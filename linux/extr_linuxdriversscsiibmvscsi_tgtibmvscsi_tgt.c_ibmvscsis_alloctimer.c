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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct timer_cb {int started; scalar_t__ timer_pops; TYPE_1__ timer; } ;
struct scsi_info {struct timer_cb rsp_q_timer; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_service_wait_q ; 

__attribute__((used)) static long ibmvscsis_alloctimer(struct scsi_info *vscsi)
{
	struct timer_cb *p_timer;

	p_timer = &vscsi->rsp_q_timer;
	hrtimer_init(&p_timer->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	p_timer->timer.function = ibmvscsis_service_wait_q;
	p_timer->started = false;
	p_timer->timer_pops = 0;

	return ADAPT_SUCCESS;
}