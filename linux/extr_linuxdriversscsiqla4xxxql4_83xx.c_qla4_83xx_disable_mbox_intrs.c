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
typedef  int uint32_t ;
struct scsi_qla_host {TYPE_1__* qla4_83xx_reg; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  leg_int_mask; int /*<<< orphan*/  mbox_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_83XX_MBOX_INTR_ON ; 
 int INT_ENABLE_FW_MB ; 
 int readl (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla4_83xx_disable_mbox_intrs(struct scsi_qla_host *ha)
{
	uint32_t mb_int, ret;

	if (test_and_clear_bit(AF_83XX_MBOX_INTR_ON, &ha->flags)) {
		ret = readl(&ha->qla4_83xx_reg->mbox_int);
		mb_int = ret & ~INT_ENABLE_FW_MB;
		writel(mb_int, &ha->qla4_83xx_reg->mbox_int);
		writel(1, &ha->qla4_83xx_reg->leg_int_mask);
	}
}