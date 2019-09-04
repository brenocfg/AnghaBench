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
struct ib_event {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_event_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_rdma_qp_event(struct ib_event *event, void *context)
{
	pr_debug("QP event %s (%d)\n",
		 ib_event_msg(event->event), event->event);

}