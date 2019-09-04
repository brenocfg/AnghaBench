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
struct wcn36xx_hal_print_reg_info_ind {int count; TYPE_1__* regs; int /*<<< orphan*/  reason; int /*<<< orphan*/  scenario; } ;
struct wcn36xx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

__attribute__((used)) static int wcn36xx_smd_print_reg_info_ind(struct wcn36xx *wcn,
					  void *buf,
					  size_t len)
{
	struct wcn36xx_hal_print_reg_info_ind *rsp = buf;
	int i;

	if (len < sizeof(*rsp)) {
		wcn36xx_warn("Corrupted print reg info indication\n");
		return -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "reginfo indication, scenario: 0x%x reason: 0x%x\n",
		    rsp->scenario, rsp->reason);

	for (i = 0; i < rsp->count; i++) {
		wcn36xx_dbg(WCN36XX_DBG_HAL, "\t0x%x: 0x%x\n",
			    rsp->regs[i].addr, rsp->regs[i].value);
	}

	return 0;
}