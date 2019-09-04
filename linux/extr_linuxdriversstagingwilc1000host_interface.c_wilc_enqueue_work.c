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
struct host_if_msg {int /*<<< orphan*/  work; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_workqueue ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wilc_enqueue_work(struct host_if_msg *msg)
{
	INIT_WORK(&msg->work, msg->fn);
	if (!hif_workqueue || !queue_work(hif_workqueue, &msg->work))
		return -EINVAL;

	return 0;
}