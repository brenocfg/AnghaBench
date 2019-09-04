#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  delayed_disc_tmo; int /*<<< orphan*/  els_tmofunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 

void
lpfc_stop_vport_timers(struct lpfc_vport *vport)
{
	del_timer_sync(&vport->els_tmofunc);
	del_timer_sync(&vport->delayed_disc_tmo);
	lpfc_can_disctmo(vport);
	return;
}