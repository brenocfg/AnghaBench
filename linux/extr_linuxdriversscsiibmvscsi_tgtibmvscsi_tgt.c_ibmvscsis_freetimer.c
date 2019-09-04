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
struct timer_cb {int started; scalar_t__ timer_pops; int /*<<< orphan*/  timer; } ;
struct scsi_info {struct timer_cb rsp_q_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvscsis_freetimer(struct scsi_info *vscsi)
{
	struct timer_cb *p_timer;

	p_timer = &vscsi->rsp_q_timer;

	(void)hrtimer_cancel(&p_timer->timer);

	p_timer->started = false;
	p_timer->timer_pops = 0;
}