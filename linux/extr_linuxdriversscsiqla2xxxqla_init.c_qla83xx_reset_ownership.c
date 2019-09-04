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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int nic_core_reset_owner; } ;
struct qla_hw_data {int portnum; TYPE_1__ flags; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA8044_CRB_DEV_PART_INFO2 ; 
 int /*<<< orphan*/  QLA8044_CRB_DEV_PART_INFO_INDEX ; 
 int /*<<< orphan*/  QLA8044_CRB_DRV_ACTIVE_INDEX ; 
 int QLA83XX_CLASS_TYPE_FCOE ; 
 int /*<<< orphan*/  QLA83XX_DEV_PARTINFO1 ; 
 int /*<<< orphan*/  QLA83XX_DEV_PARTINFO2 ; 
 int /*<<< orphan*/  QLA83XX_IDC_DRV_PRESENCE ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int qla8044_rd_direct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_rd_reg (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

void
qla83xx_reset_ownership(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t drv_presence, drv_presence_mask;
	uint32_t dev_part_info1, dev_part_info2, class_type;
	uint32_t class_type_mask = 0x3;
	uint16_t fcoe_other_function = 0xffff, i;

	if (IS_QLA8044(ha)) {
		drv_presence = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_ACTIVE_INDEX);
		dev_part_info1 = qla8044_rd_direct(vha,
		    QLA8044_CRB_DEV_PART_INFO_INDEX);
		dev_part_info2 = qla8044_rd_direct(vha,
		    QLA8044_CRB_DEV_PART_INFO2);
	} else {
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
		qla83xx_rd_reg(vha, QLA83XX_DEV_PARTINFO1, &dev_part_info1);
		qla83xx_rd_reg(vha, QLA83XX_DEV_PARTINFO2, &dev_part_info2);
	}
	for (i = 0; i < 8; i++) {
		class_type = ((dev_part_info1 >> (i * 4)) & class_type_mask);
		if ((class_type == QLA83XX_CLASS_TYPE_FCOE) &&
		    (i != ha->portnum)) {
			fcoe_other_function = i;
			break;
		}
	}
	if (fcoe_other_function == 0xffff) {
		for (i = 0; i < 8; i++) {
			class_type = ((dev_part_info2 >> (i * 4)) &
			    class_type_mask);
			if ((class_type == QLA83XX_CLASS_TYPE_FCOE) &&
			    ((i + 8) != ha->portnum)) {
				fcoe_other_function = i + 8;
				break;
			}
		}
	}
	/*
	 * Prepare drv-presence mask based on fcoe functions present.
	 * However consider only valid physical fcoe function numbers (0-15).
	 */
	drv_presence_mask = ~((1 << (ha->portnum)) |
			((fcoe_other_function == 0xffff) ?
			 0 : (1 << (fcoe_other_function))));

	/* We are the reset owner iff:
	 *    - No other protocol drivers present.
	 *    - This is the lowest among fcoe functions. */
	if (!(drv_presence & drv_presence_mask) &&
			(ha->portnum < fcoe_other_function)) {
		ql_dbg(ql_dbg_p3p, vha, 0xb07f,
		    "This host is Reset owner.\n");
		ha->flags.nic_core_reset_owner = 1;
	}
}