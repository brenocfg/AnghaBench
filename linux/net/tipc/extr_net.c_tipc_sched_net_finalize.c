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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_net_work {int /*<<< orphan*/  work; int /*<<< orphan*/  addr; struct net* net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tipc_net_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_finalize_work ; 

void tipc_sched_net_finalize(struct net *net, u32 addr)
{
	struct tipc_net_work *fwork = kzalloc(sizeof(*fwork), GFP_ATOMIC);

	if (!fwork)
		return;
	INIT_WORK(&fwork->work, tipc_net_finalize_work);
	fwork->net = net;
	fwork->addr = addr;
	schedule_work(&fwork->work);
}