#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct req_que {int /*<<< orphan*/  dma; scalar_t__ ring; } ;
struct qla_hw_data {int flt_region_fw_sec; int fw_transfer_size; int* fw_dump_template; int fw_dump_template_len; struct req_que** req_q_map; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int FA_RISC_CODE_SEGMENTS ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ QLA27XX_SECONDARY_IMAGE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int be32_to_cpu (int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_read_flash_data (TYPE_1__*,int*,int,int) ; 
 scalar_t__ qla27xx_find_valid_image (TYPE_1__*) ; 
 int /*<<< orphan*/  qla27xx_fwdt_template_default () ; 
 int qla27xx_fwdt_template_default_size () ; 
 int qla27xx_fwdt_template_size (int*) ; 
 int /*<<< orphan*/  qla27xx_fwdt_template_valid (int*) ; 
 int qla2x00_load_ram (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int swab32 (int) ; 
 int /*<<< orphan*/  vfree (int*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int
qla24xx_load_risc_flash(scsi_qla_host_t *vha, uint32_t *srisc_addr,
    uint32_t faddr)
{
	int	rval = QLA_SUCCESS;
	int	segments, fragment;
	uint32_t *dcode, dlen;
	uint32_t risc_addr;
	uint32_t risc_size;
	uint32_t i;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "FW: Loading firmware from flash (%x).\n", faddr);

	rval = QLA_SUCCESS;

	segments = FA_RISC_CODE_SEGMENTS;
	dcode = (uint32_t *)req->ring;
	*srisc_addr = 0;

	if (IS_QLA27XX(ha) &&
	    qla27xx_find_valid_image(vha) == QLA27XX_SECONDARY_IMAGE)
		faddr = ha->flt_region_fw_sec;

	/* Validate firmware image by checking version. */
	qla24xx_read_flash_data(vha, dcode, faddr + 4, 4);
	for (i = 0; i < 4; i++)
		dcode[i] = be32_to_cpu(dcode[i]);
	if ((dcode[0] == 0xffffffff && dcode[1] == 0xffffffff &&
	    dcode[2] == 0xffffffff && dcode[3] == 0xffffffff) ||
	    (dcode[0] == 0 && dcode[1] == 0 && dcode[2] == 0 &&
		dcode[3] == 0)) {
		ql_log(ql_log_fatal, vha, 0x008c,
		    "Unable to verify the integrity of flash firmware "
		    "image.\n");
		ql_log(ql_log_fatal, vha, 0x008d,
		    "Firmware data: %08x %08x %08x %08x.\n",
		    dcode[0], dcode[1], dcode[2], dcode[3]);

		return QLA_FUNCTION_FAILED;
	}

	while (segments && rval == QLA_SUCCESS) {
		/* Read segment's load information. */
		qla24xx_read_flash_data(vha, dcode, faddr, 4);

		risc_addr = be32_to_cpu(dcode[2]);
		*srisc_addr = *srisc_addr == 0 ? risc_addr : *srisc_addr;
		risc_size = be32_to_cpu(dcode[3]);

		fragment = 0;
		while (risc_size > 0 && rval == QLA_SUCCESS) {
			dlen = (uint32_t)(ha->fw_transfer_size >> 2);
			if (dlen > risc_size)
				dlen = risc_size;

			ql_dbg(ql_dbg_init, vha, 0x008e,
			    "Loading risc segment@ risc addr %x "
			    "number of dwords 0x%x offset 0x%x.\n",
			    risc_addr, dlen, faddr);

			qla24xx_read_flash_data(vha, dcode, faddr, dlen);
			for (i = 0; i < dlen; i++)
				dcode[i] = swab32(dcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr,
			    dlen);
			if (rval) {
				ql_log(ql_log_fatal, vha, 0x008f,
				    "Failed to load segment %d of firmware.\n",
				    fragment);
				return QLA_FUNCTION_FAILED;
			}

			faddr += dlen;
			risc_addr += dlen;
			risc_size -= dlen;
			fragment++;
		}

		/* Next segment. */
		segments--;
	}

	if (!IS_QLA27XX(ha))
		return rval;

	if (ha->fw_dump_template)
		vfree(ha->fw_dump_template);
	ha->fw_dump_template = NULL;
	ha->fw_dump_template_len = 0;

	ql_dbg(ql_dbg_init, vha, 0x0161,
	    "Loading fwdump template from %x\n", faddr);
	qla24xx_read_flash_data(vha, dcode, faddr, 7);
	risc_size = be32_to_cpu(dcode[2]);
	ql_dbg(ql_dbg_init, vha, 0x0162,
	    "-> array size %x dwords\n", risc_size);
	if (risc_size == 0 || risc_size == ~0)
		goto default_template;

	dlen = (risc_size - 8) * sizeof(*dcode);
	ql_dbg(ql_dbg_init, vha, 0x0163,
	    "-> template allocating %x bytes...\n", dlen);
	ha->fw_dump_template = vmalloc(dlen);
	if (!ha->fw_dump_template) {
		ql_log(ql_log_warn, vha, 0x0164,
		    "Failed fwdump template allocate %x bytes.\n", risc_size);
		goto default_template;
	}

	faddr += 7;
	risc_size -= 8;
	dcode = ha->fw_dump_template;
	qla24xx_read_flash_data(vha, dcode, faddr, risc_size);
	for (i = 0; i < risc_size; i++)
		dcode[i] = le32_to_cpu(dcode[i]);

	if (!qla27xx_fwdt_template_valid(dcode)) {
		ql_log(ql_log_warn, vha, 0x0165,
		    "Failed fwdump template validate\n");
		goto default_template;
	}

	dlen = qla27xx_fwdt_template_size(dcode);
	ql_dbg(ql_dbg_init, vha, 0x0166,
	    "-> template size %x bytes\n", dlen);
	if (dlen > risc_size * sizeof(*dcode)) {
		ql_log(ql_log_warn, vha, 0x0167,
		    "Failed fwdump template exceeds array by %zx bytes\n",
		    (size_t)(dlen - risc_size * sizeof(*dcode)));
		goto default_template;
	}
	ha->fw_dump_template_len = dlen;
	return rval;

default_template:
	ql_log(ql_log_warn, vha, 0x0168, "Using default fwdump template\n");
	if (ha->fw_dump_template)
		vfree(ha->fw_dump_template);
	ha->fw_dump_template = NULL;
	ha->fw_dump_template_len = 0;

	dlen = qla27xx_fwdt_template_default_size();
	ql_dbg(ql_dbg_init, vha, 0x0169,
	    "-> template allocating %x bytes...\n", dlen);
	ha->fw_dump_template = vmalloc(dlen);
	if (!ha->fw_dump_template) {
		ql_log(ql_log_warn, vha, 0x016a,
		    "Failed fwdump template allocate %x bytes.\n", risc_size);
		goto failed_template;
	}

	dcode = ha->fw_dump_template;
	risc_size = dlen / sizeof(*dcode);
	memcpy(dcode, qla27xx_fwdt_template_default(), dlen);
	for (i = 0; i < risc_size; i++)
		dcode[i] = be32_to_cpu(dcode[i]);

	if (!qla27xx_fwdt_template_valid(ha->fw_dump_template)) {
		ql_log(ql_log_warn, vha, 0x016b,
		    "Failed fwdump template validate\n");
		goto failed_template;
	}

	dlen = qla27xx_fwdt_template_size(ha->fw_dump_template);
	ql_dbg(ql_dbg_init, vha, 0x016c,
	    "-> template size %x bytes\n", dlen);
	ha->fw_dump_template_len = dlen;
	return rval;

failed_template:
	ql_log(ql_log_warn, vha, 0x016d, "Failed default fwdump template\n");
	if (ha->fw_dump_template)
		vfree(ha->fw_dump_template);
	ha->fw_dump_template = NULL;
	ha->fw_dump_template_len = 0;
	return rval;
}