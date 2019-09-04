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
struct TYPE_4__ {int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct ipr_cmnd {TYPE_2__ timer; int /*<<< orphan*/  done; TYPE_1__* hrrq; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  hrrq_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_reset_timer_done ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_reset_start_timer(struct ipr_cmnd *ipr_cmd,
				  unsigned long timeout)
{

	ENTER;
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
	ipr_cmd->done = ipr_reset_ioa_job;

	ipr_cmd->timer.expires = jiffies + timeout;
	ipr_cmd->timer.function = ipr_reset_timer_done;
	add_timer(&ipr_cmd->timer);
}