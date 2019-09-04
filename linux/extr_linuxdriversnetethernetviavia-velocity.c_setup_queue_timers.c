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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  rxqueue_timer; int /*<<< orphan*/  txqueue_timer; } ;
struct velocity_info {scalar_t__ rev_id; int mii_status; TYPE_1__* mac_regs; TYPE_2__ options; } ;
struct TYPE_3__ {int /*<<< orphan*/  RQETMR; int /*<<< orphan*/  TQETMR; } ;

/* Variables and functions */
 scalar_t__ REV_ID_VT3216_A0 ; 
 int VELOCITY_SPEED_100 ; 
 int VELOCITY_SPEED_1000 ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_queue_timers(struct velocity_info *vptr)
{
	/* Only for newer revisions */
	if (vptr->rev_id >= REV_ID_VT3216_A0) {
		u8 txqueue_timer = 0;
		u8 rxqueue_timer = 0;

		if (vptr->mii_status & (VELOCITY_SPEED_1000 |
				VELOCITY_SPEED_100)) {
			txqueue_timer = vptr->options.txqueue_timer;
			rxqueue_timer = vptr->options.rxqueue_timer;
		}

		writeb(txqueue_timer, &vptr->mac_regs->TQETMR);
		writeb(rxqueue_timer, &vptr->mac_regs->RQETMR);
	}
}