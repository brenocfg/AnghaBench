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
struct visorhba_devdata {int /*<<< orphan*/  thread_wait_ms; int /*<<< orphan*/  interrupt_rcvd; int /*<<< orphan*/  rsp_queue; } ;
struct uiscmdrsp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_queue (struct uiscmdrsp*,struct visorhba_devdata*) ; 
 int /*<<< orphan*/  kfree (struct uiscmdrsp*) ; 
 struct uiscmdrsp* kmalloc (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_incoming_rsps(void *v)
{
	struct visorhba_devdata *devdata = v;
	struct uiscmdrsp *cmdrsp = NULL;
	const int size = sizeof(*cmdrsp);

	cmdrsp = kmalloc(size, GFP_ATOMIC);
	if (!cmdrsp)
		return -ENOMEM;

	while (1) {
		if (kthread_should_stop())
			break;
		wait_event_interruptible_timeout(
			devdata->rsp_queue, (atomic_read(
					     &devdata->interrupt_rcvd) == 1),
				msecs_to_jiffies(devdata->thread_wait_ms));
		/* drain queue */
		drain_queue(cmdrsp, devdata);
	}
	kfree(cmdrsp);
	return 0;
}