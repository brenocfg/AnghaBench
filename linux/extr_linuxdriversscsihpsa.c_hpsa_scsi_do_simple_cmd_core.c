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
struct ctlr_info {TYPE_1__* pdev; } ;
struct CommandList {int /*<<< orphan*/ * waiting; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int IO_OK ; 
 unsigned long NO_TIMEOUT ; 
 int /*<<< orphan*/  __enqueue_cmd_and_start_io (struct ctlr_info*,struct CommandList*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_scsi_do_simple_cmd_core(struct ctlr_info *h,
	struct CommandList *c, int reply_queue, unsigned long timeout_msecs)
{
	DECLARE_COMPLETION_ONSTACK(wait);

	c->waiting = &wait;
	__enqueue_cmd_and_start_io(h, c, reply_queue);
	if (timeout_msecs == NO_TIMEOUT) {
		/* TODO: get rid of this no-timeout thing */
		wait_for_completion_io(&wait);
		return IO_OK;
	}
	if (!wait_for_completion_io_timeout(&wait,
					msecs_to_jiffies(timeout_msecs))) {
		dev_warn(&h->pdev->dev, "Command timed out.\n");
		return -ETIMEDOUT;
	}
	return IO_OK;
}