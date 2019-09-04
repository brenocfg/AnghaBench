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
struct tipc_topsrv {int /*<<< orphan*/  send_wq; int /*<<< orphan*/  rcv_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_topsrv_work_stop(struct tipc_topsrv *s)
{
	destroy_workqueue(s->rcv_wq);
	destroy_workqueue(s->send_wq);
}