#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct qla_hw_data {int* bios_revision; int* efi_revision; int* fcode_revision; int* fw_revision; int flt_region_fw; int /*<<< orphan*/  pio_address; } ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int BIT_7 ; 
 scalar_t__ IS_QLA2322 (struct qla_hw_data*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
#define  ROM_CODE_TYPE_BIOS 130 
#define  ROM_CODE_TYPE_EFI 129 
#define  ROM_CODE_TYPE_FCODE 128 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_1__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_init ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_1__*,int,int*,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_flash_disable (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_flash_enable (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_get_fcode_version (struct qla_hw_data*,int) ; 
 int qla2x00_read_flash_byte (struct qla_hw_data*,int) ; 
 int /*<<< orphan*/  qla2x00_read_flash_data (struct qla_hw_data*,int*,int,int) ; 

int
qla2x00_get_flash_version(scsi_qla_host_t *vha, void *mbuf)
{
	int ret = QLA_SUCCESS;
	uint8_t code_type, last_image;
	uint32_t pcihdr, pcids;
	uint8_t *dbyte;
	uint16_t *dcode;
	struct qla_hw_data *ha = vha->hw;

	if (!ha->pio_address || !mbuf)
		return QLA_FUNCTION_FAILED;

	memset(ha->bios_revision, 0, sizeof(ha->bios_revision));
	memset(ha->efi_revision, 0, sizeof(ha->efi_revision));
	memset(ha->fcode_revision, 0, sizeof(ha->fcode_revision));
	memset(ha->fw_revision, 0, sizeof(ha->fw_revision));

	qla2x00_flash_enable(ha);

	/* Begin with first PCI expansion ROM header. */
	pcihdr = 0;
	last_image = 1;
	do {
		/* Verify PCI expansion ROM header. */
		if (qla2x00_read_flash_byte(ha, pcihdr) != 0x55 ||
		    qla2x00_read_flash_byte(ha, pcihdr + 0x01) != 0xaa) {
			/* No signature */
			ql_log(ql_log_fatal, vha, 0x0050,
			    "No matching ROM signature.\n");
			ret = QLA_FUNCTION_FAILED;
			break;
		}

		/* Locate PCI data structure. */
		pcids = pcihdr +
		    ((qla2x00_read_flash_byte(ha, pcihdr + 0x19) << 8) |
			qla2x00_read_flash_byte(ha, pcihdr + 0x18));

		/* Validate signature of PCI data structure. */
		if (qla2x00_read_flash_byte(ha, pcids) != 'P' ||
		    qla2x00_read_flash_byte(ha, pcids + 0x1) != 'C' ||
		    qla2x00_read_flash_byte(ha, pcids + 0x2) != 'I' ||
		    qla2x00_read_flash_byte(ha, pcids + 0x3) != 'R') {
			/* Incorrect header. */
			ql_log(ql_log_fatal, vha, 0x0051,
			    "PCI data struct not found pcir_adr=%x.\n", pcids);
			ret = QLA_FUNCTION_FAILED;
			break;
		}

		/* Read version */
		code_type = qla2x00_read_flash_byte(ha, pcids + 0x14);
		switch (code_type) {
		case ROM_CODE_TYPE_BIOS:
			/* Intel x86, PC-AT compatible. */
			ha->bios_revision[0] =
			    qla2x00_read_flash_byte(ha, pcids + 0x12);
			ha->bios_revision[1] =
			    qla2x00_read_flash_byte(ha, pcids + 0x13);
			ql_dbg(ql_dbg_init, vha, 0x0052,
			    "Read BIOS %d.%d.\n",
			    ha->bios_revision[1], ha->bios_revision[0]);
			break;
		case ROM_CODE_TYPE_FCODE:
			/* Open Firmware standard for PCI (FCode). */
			/* Eeeewww... */
			qla2x00_get_fcode_version(ha, pcids);
			break;
		case ROM_CODE_TYPE_EFI:
			/* Extensible Firmware Interface (EFI). */
			ha->efi_revision[0] =
			    qla2x00_read_flash_byte(ha, pcids + 0x12);
			ha->efi_revision[1] =
			    qla2x00_read_flash_byte(ha, pcids + 0x13);
			ql_dbg(ql_dbg_init, vha, 0x0053,
			    "Read EFI %d.%d.\n",
			    ha->efi_revision[1], ha->efi_revision[0]);
			break;
		default:
			ql_log(ql_log_warn, vha, 0x0054,
			    "Unrecognized code type %x at pcids %x.\n",
			    code_type, pcids);
			break;
		}

		last_image = qla2x00_read_flash_byte(ha, pcids + 0x15) & BIT_7;

		/* Locate next PCI expansion ROM. */
		pcihdr += ((qla2x00_read_flash_byte(ha, pcids + 0x11) << 8) |
		    qla2x00_read_flash_byte(ha, pcids + 0x10)) * 512;
	} while (!last_image);

	if (IS_QLA2322(ha)) {
		/* Read firmware image information. */
		memset(ha->fw_revision, 0, sizeof(ha->fw_revision));
		dbyte = mbuf;
		memset(dbyte, 0, 8);
		dcode = (uint16_t *)dbyte;

		qla2x00_read_flash_data(ha, dbyte, ha->flt_region_fw * 4 + 10,
		    8);
		ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x010a,
		    "Dumping fw "
		    "ver from flash:.\n");
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x010b,
		    (uint8_t *)dbyte, 8);

		if ((dcode[0] == 0xffff && dcode[1] == 0xffff &&
		    dcode[2] == 0xffff && dcode[3] == 0xffff) ||
		    (dcode[0] == 0 && dcode[1] == 0 && dcode[2] == 0 &&
		    dcode[3] == 0)) {
			ql_log(ql_log_warn, vha, 0x0057,
			    "Unrecognized fw revision at %x.\n",
			    ha->flt_region_fw * 4);
		} else {
			/* values are in big endian */
			ha->fw_revision[0] = dbyte[0] << 16 | dbyte[1];
			ha->fw_revision[1] = dbyte[2] << 16 | dbyte[3];
			ha->fw_revision[2] = dbyte[4] << 16 | dbyte[5];
			ql_dbg(ql_dbg_init, vha, 0x0058,
			    "FW Version: "
			    "%d.%d.%d.\n", ha->fw_revision[0],
			    ha->fw_revision[1], ha->fw_revision[2]);
		}
	}

	qla2x00_flash_disable(ha);

	return ret;
}