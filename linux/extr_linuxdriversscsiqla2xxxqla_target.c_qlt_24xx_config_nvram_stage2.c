#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  init_done; } ;
struct scsi_qla_host {TYPE_1__ flags; struct qla_hw_data* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  tgt_node_name; scalar_t__ node_name_set; } ;
struct qla_hw_data {TYPE_2__ tgt; } ;
struct init_cb_24xx {int /*<<< orphan*/  firmware_options_2; int /*<<< orphan*/  firmware_options_1; int /*<<< orphan*/  node_name; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_14 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int /*<<< orphan*/  QLA_TGT_MODE_ENABLED () ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qlt_24xx_config_nvram_stage2(struct scsi_qla_host *vha,
	struct init_cb_24xx *icb)
{
	struct qla_hw_data *ha = vha->hw;

	if (!QLA_TGT_MODE_ENABLED())
		return;

	if (ha->tgt.node_name_set) {
		memcpy(icb->node_name, ha->tgt.tgt_node_name, WWN_SIZE);
		icb->firmware_options_1 |= cpu_to_le32(BIT_14);
	}

	/* disable ZIO at start time. */
	if (!vha->flags.init_done) {
		uint32_t tmp;
		tmp = le32_to_cpu(icb->firmware_options_2);
		tmp &= ~(BIT_3 | BIT_2 | BIT_1 | BIT_0);
		icb->firmware_options_2 = cpu_to_le32(tmp);
	}
}