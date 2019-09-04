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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  heartbeat; } ;
struct bfa_ioc_s {scalar_t__ hb_count; TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_hb_timer_start (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_poll (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_recover (struct bfa_ioc_s*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_hb_check(void *cbarg)
{
	struct bfa_ioc_s  *ioc = cbarg;
	u32	hb_count;

	hb_count = readl(ioc->ioc_regs.heartbeat);
	if (ioc->hb_count == hb_count) {
		bfa_ioc_recover(ioc);
		return;
	} else {
		ioc->hb_count = hb_count;
	}

	bfa_ioc_mbox_poll(ioc);
	bfa_hb_timer_start(ioc);
}