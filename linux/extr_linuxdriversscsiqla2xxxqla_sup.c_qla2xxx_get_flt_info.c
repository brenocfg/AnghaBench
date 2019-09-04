#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct req_que {scalar_t__ ring; } ;
struct qla_hw_data {size_t flt_region_fcp_prio; scalar_t__ port_no; size_t flt_region_flt; size_t flt_region_fw; size_t flt_region_boot; size_t flt_region_vpd_nvram; size_t flt_region_vpd; size_t flt_region_nvram; size_t flt_region_fdt; size_t flt_region_npiv_conf; size_t flt_region_gold_fw; size_t flt_region_bootload; size_t flt_region_img_status_pri; size_t flt_region_img_status_sec; size_t flt_region_fw_sec; size_t flt_region_boot_sec; size_t flt_region_vpd_sec; TYPE_1__* isp_ops; struct req_que** req_q_map; } ;
struct qla_flt_region {int /*<<< orphan*/  code; int /*<<< orphan*/  size; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct qla_flt_header {scalar_t__ version; scalar_t__ length; scalar_t__ checksum; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* read_optrom ) (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t const FA_BOOT_CODE_ADDR ; 
 size_t const FA_BOOT_CODE_ADDR_81 ; 
 size_t const FA_FCP_PRIO0_ADDR ; 
 size_t const FA_FCP_PRIO0_ADDR_25 ; 
 size_t const FA_FCP_PRIO1_ADDR ; 
 size_t const FA_FCP_PRIO1_ADDR_25 ; 
 size_t const FA_FLASH_DESCR_ADDR ; 
 size_t const FA_FLASH_DESCR_ADDR_24 ; 
 size_t const FA_FLASH_DESCR_ADDR_81 ; 
 size_t const FA_NPIV_CONF0_ADDR ; 
 size_t const FA_NPIV_CONF0_ADDR_24 ; 
 size_t const FA_NPIV_CONF0_ADDR_81 ; 
 size_t const FA_NPIV_CONF1_ADDR ; 
 size_t const FA_NPIV_CONF1_ADDR_24 ; 
 size_t const FA_NPIV_CONF1_ADDR_81 ; 
 size_t const FA_NVRAM0_ADDR_81 ; 
 size_t const FA_NVRAM1_ADDR_81 ; 
 size_t const FA_RISC_CODE_ADDR ; 
 size_t const FA_RISC_CODE_ADDR_81 ; 
 size_t const FA_VPD0_ADDR_81 ; 
 size_t const FA_VPD1_ADDR_81 ; 
 size_t const FA_VPD_NVRAM_ADDR ; 
 size_t const FA_VPD_NVRAM_ADDR_81 ; 
#define  FLT_REG_BOOTLOAD_82XX 161 
#define  FLT_REG_BOOTLOAD_SEC_27XX 160 
#define  FLT_REG_BOOT_CODE 159 
#define  FLT_REG_BOOT_CODE_8044 158 
#define  FLT_REG_BOOT_CODE_82XX 157 
#define  FLT_REG_CNA_FW 156 
#define  FLT_REG_FCOE_FW 155 
#define  FLT_REG_FCOE_NVRAM_0 154 
#define  FLT_REG_FCOE_NVRAM_1 153 
#define  FLT_REG_FCP_PRIO_0 152 
#define  FLT_REG_FCP_PRIO_1 151 
#define  FLT_REG_FDT 150 
#define  FLT_REG_FW 149 
#define  FLT_REG_FW_82XX 148 
#define  FLT_REG_FW_SEC_27XX 147 
#define  FLT_REG_GOLD_FW 146 
#define  FLT_REG_GOLD_FW_82XX 145 
#define  FLT_REG_IMG_PRI_27XX 144 
#define  FLT_REG_IMG_SEC_27XX 143 
#define  FLT_REG_NPIV_CONF_0 142 
#define  FLT_REG_NPIV_CONF_1 141 
#define  FLT_REG_NVRAM_0 140 
#define  FLT_REG_NVRAM_1 139 
#define  FLT_REG_NVRAM_2 138 
#define  FLT_REG_NVRAM_3 137 
#define  FLT_REG_VPD_0 136 
#define  FLT_REG_VPD_1 135 
#define  FLT_REG_VPD_2 134 
#define  FLT_REG_VPD_3 133 
#define  FLT_REG_VPD_8XXX 132 
#define  FLT_REG_VPD_SEC_27XX_0 131 
#define  FLT_REG_VPD_SEC_27XX_1 130 
#define  FLT_REG_VPD_SEC_27XX_2 129 
#define  FLT_REG_VPD_SEC_27XX_3 128 
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_P3P_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA8031 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA8044 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA81XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  OPTROM_BURST_SIZE ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int le16_to_cpu (scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla2xxx_get_flt_info(scsi_qla_host_t *vha, uint32_t flt_addr)
{
	const char *loc, *locations[] = { "DEF", "FLT" };
	const uint32_t def_fw[] =
		{ FA_RISC_CODE_ADDR, FA_RISC_CODE_ADDR, FA_RISC_CODE_ADDR_81 };
	const uint32_t def_boot[] =
		{ FA_BOOT_CODE_ADDR, FA_BOOT_CODE_ADDR, FA_BOOT_CODE_ADDR_81 };
	const uint32_t def_vpd_nvram[] =
		{ FA_VPD_NVRAM_ADDR, FA_VPD_NVRAM_ADDR, FA_VPD_NVRAM_ADDR_81 };
	const uint32_t def_vpd0[] =
		{ 0, 0, FA_VPD0_ADDR_81 };
	const uint32_t def_vpd1[] =
		{ 0, 0, FA_VPD1_ADDR_81 };
	const uint32_t def_nvram0[] =
		{ 0, 0, FA_NVRAM0_ADDR_81 };
	const uint32_t def_nvram1[] =
		{ 0, 0, FA_NVRAM1_ADDR_81 };
	const uint32_t def_fdt[] =
		{ FA_FLASH_DESCR_ADDR_24, FA_FLASH_DESCR_ADDR,
			FA_FLASH_DESCR_ADDR_81 };
	const uint32_t def_npiv_conf0[] =
		{ FA_NPIV_CONF0_ADDR_24, FA_NPIV_CONF0_ADDR,
			FA_NPIV_CONF0_ADDR_81 };
	const uint32_t def_npiv_conf1[] =
		{ FA_NPIV_CONF1_ADDR_24, FA_NPIV_CONF1_ADDR,
			FA_NPIV_CONF1_ADDR_81 };
	const uint32_t fcp_prio_cfg0[] =
		{ FA_FCP_PRIO0_ADDR, FA_FCP_PRIO0_ADDR_25,
			0 };
	const uint32_t fcp_prio_cfg1[] =
		{ FA_FCP_PRIO1_ADDR, FA_FCP_PRIO1_ADDR_25,
			0 };
	uint32_t def;
	uint16_t *wptr;
	uint16_t cnt, chksum;
	uint32_t start;
	struct qla_flt_header *flt;
	struct qla_flt_region *region;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];

	def = 0;
	if (IS_QLA25XX(ha))
		def = 1;
	else if (IS_QLA81XX(ha))
		def = 2;

	/* Assign FCP prio region since older adapters may not have FLT, or
	   FCP prio region in it's FLT.
	 */
	ha->flt_region_fcp_prio = (ha->port_no == 0) ?
	    fcp_prio_cfg0[def] : fcp_prio_cfg1[def];

	ha->flt_region_flt = flt_addr;
	wptr = (uint16_t *)req->ring;
	flt = (struct qla_flt_header *)req->ring;
	region = (struct qla_flt_region *)&flt[1];
	ha->isp_ops->read_optrom(vha, (uint8_t *)req->ring,
	    flt_addr << 2, OPTROM_BURST_SIZE);
	if (*wptr == cpu_to_le16(0xffff))
		goto no_flash_data;
	if (flt->version != cpu_to_le16(1)) {
		ql_log(ql_log_warn, vha, 0x0047,
		    "Unsupported FLT detected: version=0x%x length=0x%x checksum=0x%x.\n",
		    le16_to_cpu(flt->version), le16_to_cpu(flt->length),
		    le16_to_cpu(flt->checksum));
		goto no_flash_data;
	}

	cnt = (sizeof(struct qla_flt_header) + le16_to_cpu(flt->length)) >> 1;
	for (chksum = 0; cnt--; wptr++)
		chksum += le16_to_cpu(*wptr);
	if (chksum) {
		ql_log(ql_log_fatal, vha, 0x0048,
		    "Inconsistent FLT detected: version=0x%x length=0x%x checksum=0x%x.\n",
		    le16_to_cpu(flt->version), le16_to_cpu(flt->length),
		    le16_to_cpu(flt->checksum));
		goto no_flash_data;
	}

	loc = locations[1];
	cnt = le16_to_cpu(flt->length) / sizeof(struct qla_flt_region);
	for ( ; cnt; cnt--, region++) {
		/* Store addresses as DWORD offsets. */
		start = le32_to_cpu(region->start) >> 2;
		ql_dbg(ql_dbg_init, vha, 0x0049,
		    "FLT[%02x]: start=0x%x "
		    "end=0x%x size=0x%x.\n", le32_to_cpu(region->code) & 0xff,
		    start, le32_to_cpu(region->end) >> 2,
		    le32_to_cpu(region->size));

		switch (le32_to_cpu(region->code) & 0xff) {
		case FLT_REG_FCOE_FW:
			if (!IS_QLA8031(ha))
				break;
			ha->flt_region_fw = start;
			break;
		case FLT_REG_FW:
			if (IS_QLA8031(ha))
				break;
			ha->flt_region_fw = start;
			break;
		case FLT_REG_BOOT_CODE:
			ha->flt_region_boot = start;
			break;
		case FLT_REG_VPD_0:
			if (IS_QLA8031(ha))
				break;
			ha->flt_region_vpd_nvram = start;
			if (IS_P3P_TYPE(ha))
				break;
			if (ha->port_no == 0)
				ha->flt_region_vpd = start;
			break;
		case FLT_REG_VPD_1:
			if (IS_P3P_TYPE(ha) || IS_QLA8031(ha))
				break;
			if (ha->port_no == 1)
				ha->flt_region_vpd = start;
			break;
		case FLT_REG_VPD_2:
			if (!IS_QLA27XX(ha))
				break;
			if (ha->port_no == 2)
				ha->flt_region_vpd = start;
			break;
		case FLT_REG_VPD_3:
			if (!IS_QLA27XX(ha))
				break;
			if (ha->port_no == 3)
				ha->flt_region_vpd = start;
			break;
		case FLT_REG_NVRAM_0:
			if (IS_QLA8031(ha))
				break;
			if (ha->port_no == 0)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_NVRAM_1:
			if (IS_QLA8031(ha))
				break;
			if (ha->port_no == 1)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_NVRAM_2:
			if (!IS_QLA27XX(ha))
				break;
			if (ha->port_no == 2)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_NVRAM_3:
			if (!IS_QLA27XX(ha))
				break;
			if (ha->port_no == 3)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_FDT:
			ha->flt_region_fdt = start;
			break;
		case FLT_REG_NPIV_CONF_0:
			if (ha->port_no == 0)
				ha->flt_region_npiv_conf = start;
			break;
		case FLT_REG_NPIV_CONF_1:
			if (ha->port_no == 1)
				ha->flt_region_npiv_conf = start;
			break;
		case FLT_REG_GOLD_FW:
			ha->flt_region_gold_fw = start;
			break;
		case FLT_REG_FCP_PRIO_0:
			if (ha->port_no == 0)
				ha->flt_region_fcp_prio = start;
			break;
		case FLT_REG_FCP_PRIO_1:
			if (ha->port_no == 1)
				ha->flt_region_fcp_prio = start;
			break;
		case FLT_REG_BOOT_CODE_82XX:
			ha->flt_region_boot = start;
			break;
		case FLT_REG_BOOT_CODE_8044:
			if (IS_QLA8044(ha))
				ha->flt_region_boot = start;
			break;
		case FLT_REG_FW_82XX:
			ha->flt_region_fw = start;
			break;
		case FLT_REG_CNA_FW:
			if (IS_CNA_CAPABLE(ha))
				ha->flt_region_fw = start;
			break;
		case FLT_REG_GOLD_FW_82XX:
			ha->flt_region_gold_fw = start;
			break;
		case FLT_REG_BOOTLOAD_82XX:
			ha->flt_region_bootload = start;
			break;
		case FLT_REG_VPD_8XXX:
			if (IS_CNA_CAPABLE(ha))
				ha->flt_region_vpd = start;
			break;
		case FLT_REG_FCOE_NVRAM_0:
			if (!(IS_QLA8031(ha) || IS_QLA8044(ha)))
				break;
			if (ha->port_no == 0)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_FCOE_NVRAM_1:
			if (!(IS_QLA8031(ha) || IS_QLA8044(ha)))
				break;
			if (ha->port_no == 1)
				ha->flt_region_nvram = start;
			break;
		case FLT_REG_IMG_PRI_27XX:
			if (IS_QLA27XX(ha))
				ha->flt_region_img_status_pri = start;
			break;
		case FLT_REG_IMG_SEC_27XX:
			if (IS_QLA27XX(ha))
				ha->flt_region_img_status_sec = start;
			break;
		case FLT_REG_FW_SEC_27XX:
			if (IS_QLA27XX(ha))
				ha->flt_region_fw_sec = start;
			break;
		case FLT_REG_BOOTLOAD_SEC_27XX:
			if (IS_QLA27XX(ha))
				ha->flt_region_boot_sec = start;
			break;
		case FLT_REG_VPD_SEC_27XX_0:
			if (IS_QLA27XX(ha))
				ha->flt_region_vpd_sec = start;
			break;
		case FLT_REG_VPD_SEC_27XX_1:
			if (IS_QLA27XX(ha))
				ha->flt_region_vpd_sec = start;
			break;
		case FLT_REG_VPD_SEC_27XX_2:
			if (IS_QLA27XX(ha))
				ha->flt_region_vpd_sec = start;
			break;
		case FLT_REG_VPD_SEC_27XX_3:
			if (IS_QLA27XX(ha))
				ha->flt_region_vpd_sec = start;
			break;
		}
	}
	goto done;

no_flash_data:
	/* Use hardcoded defaults. */
	loc = locations[0];
	ha->flt_region_fw = def_fw[def];
	ha->flt_region_boot = def_boot[def];
	ha->flt_region_vpd_nvram = def_vpd_nvram[def];
	ha->flt_region_vpd = (ha->port_no == 0) ?
	    def_vpd0[def] : def_vpd1[def];
	ha->flt_region_nvram = (ha->port_no == 0) ?
	    def_nvram0[def] : def_nvram1[def];
	ha->flt_region_fdt = def_fdt[def];
	ha->flt_region_npiv_conf = (ha->port_no == 0) ?
	    def_npiv_conf0[def] : def_npiv_conf1[def];
done:
	ql_dbg(ql_dbg_init, vha, 0x004a,
	    "FLT[%s]: boot=0x%x fw=0x%x vpd_nvram=0x%x vpd=0x%x nvram=0x%x "
	    "fdt=0x%x flt=0x%x npiv=0x%x fcp_prif_cfg=0x%x.\n",
	    loc, ha->flt_region_boot, ha->flt_region_fw,
	    ha->flt_region_vpd_nvram, ha->flt_region_vpd, ha->flt_region_nvram,
	    ha->flt_region_fdt, ha->flt_region_flt, ha->flt_region_npiv_conf,
	    ha->flt_region_fcp_prio);
}