#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/ * fw_options; TYPE_1__* isp_ops; int /*<<< orphan*/  beacon_color_state; scalar_t__ beacon_blink_led; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* beacon_blink ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FO1_DISABLE_GPIO6_7 ; 
 int /*<<< orphan*/  FO1_SET_EMPHASIS_SWING ; 
 scalar_t__ IS_QLA2322 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA_LED_ALL_ON ; 
 int /*<<< orphan*/  QLA_LED_GRN_ON ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_set_fw_options (struct scsi_qla_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 

int
qla2x00_beacon_off(struct scsi_qla_host *vha)
{
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;

	ha->beacon_blink_led = 0;

	/* Set the on flag so when it gets flipped it will be off. */
	if (IS_QLA2322(ha))
		ha->beacon_color_state = QLA_LED_ALL_ON;
	else
		ha->beacon_color_state = QLA_LED_GRN_ON;

	ha->isp_ops->beacon_blink(vha);	/* This turns green LED off */

	ha->fw_options[1] &= ~FO1_SET_EMPHASIS_SWING;
	ha->fw_options[1] &= ~FO1_DISABLE_GPIO6_7;

	rval = qla2x00_set_fw_options(vha, ha->fw_options);
	if (rval != QLA_SUCCESS)
		ql_log(ql_log_warn, vha, 0x709c,
		    "Unable to update fw options (beacon off).\n");
	return rval;
}