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
struct tipc_topsrv {void* rcv_wq; void* send_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int tipc_topsrv_work_start(struct tipc_topsrv *s)
{
	s->rcv_wq = alloc_ordered_workqueue("tipc_rcv", 0);
	if (!s->rcv_wq) {
		pr_err("can't start tipc receive workqueue\n");
		return -ENOMEM;
	}

	s->send_wq = alloc_ordered_workqueue("tipc_send", 0);
	if (!s->send_wq) {
		pr_err("can't start tipc send workqueue\n");
		destroy_workqueue(s->rcv_wq);
		return -ENOMEM;
	}

	return 0;
}