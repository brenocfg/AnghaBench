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
struct initio_host {scalar_t__ addr; TYPE_1__* active_tc; scalar_t__* msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  js_period; int /*<<< orphan*/  sconfig0; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_SYNC_DONE ; 
 int /*<<< orphan*/  TCF_WDTR_DONE ; 
 int /*<<< orphan*/  TSC_ALT_PERIOD ; 
 int /*<<< orphan*/  TSC_WIDE_SCSI ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SPeriod ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wdtr_done(struct initio_host * host)
{
	host->active_tc->flags &= ~TCF_SYNC_DONE;
	host->active_tc->flags |= TCF_WDTR_DONE;

	host->active_tc->js_period = 0;
	if (host->msg[2])	/* if 16 bit */
		host->active_tc->js_period |= TSC_WIDE_SCSI;
	host->active_tc->sconfig0 &= ~TSC_ALT_PERIOD;
	outb(host->active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(host->active_tc->js_period, host->addr + TUL_SPeriod);

	return 1;
}