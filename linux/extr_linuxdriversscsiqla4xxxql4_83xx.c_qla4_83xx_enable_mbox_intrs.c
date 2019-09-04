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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  flags; TYPE_1__* qla4_83xx_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  leg_int_mask; int /*<<< orphan*/  mbox_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_83XX_MBOX_INTR_ON ; 
 int /*<<< orphan*/  INT_ENABLE_FW_MB ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4_83xx_enable_mbox_intrs(struct scsi_qla_host *ha)
{
	uint32_t mb_int;

	if (!test_bit(AF_83XX_MBOX_INTR_ON, &ha->flags)) {
		mb_int = INT_ENABLE_FW_MB;
		writel(mb_int, &ha->qla4_83xx_reg->mbox_int);
		writel(0, &ha->qla4_83xx_reg->leg_int_mask);
		set_bit(AF_83XX_MBOX_INTR_ON, &ha->flags);
	}
}