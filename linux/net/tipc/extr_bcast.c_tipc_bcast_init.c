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
struct tipc_net {struct tipc_link* bcl; int /*<<< orphan*/  bclock; struct tipc_link* bcbase; } ;
struct tipc_link {int rc_ratio; int rcast_support; struct tipc_link* link; int /*<<< orphan*/  inputq; } ;
struct tipc_bc_base {int rc_ratio; int rcast_support; struct tipc_bc_base* link; int /*<<< orphan*/  inputq; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLINK_WIN_DEFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_MTU ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tipc_link*) ; 
 struct tipc_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_bc_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tipc_link**) ; 
 struct tipc_net* tipc_net (struct net*) ; 

int tipc_bcast_init(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);
	struct tipc_bc_base *bb = NULL;
	struct tipc_link *l = NULL;

	bb = kzalloc(sizeof(*bb), GFP_KERNEL);
	if (!bb)
		goto enomem;
	tn->bcbase = bb;
	spin_lock_init(&tipc_net(net)->bclock);

	if (!tipc_link_bc_create(net, 0, 0,
				 FB_MTU,
				 BCLINK_WIN_DEFAULT,
				 0,
				 &bb->inputq,
				 NULL,
				 NULL,
				 &l))
		goto enomem;
	bb->link = l;
	tn->bcl = l;
	bb->rc_ratio = 10;
	bb->rcast_support = true;
	return 0;
enomem:
	kfree(bb);
	kfree(l);
	return -ENOMEM;
}