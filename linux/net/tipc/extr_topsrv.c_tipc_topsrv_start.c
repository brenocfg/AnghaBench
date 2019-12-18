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
struct tipc_topsrv {scalar_t__ idr_in_use; int /*<<< orphan*/  conn_idr; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  name; int /*<<< orphan*/  awork; struct net* net; } ;
struct tipc_net {int /*<<< orphan*/  subscription_count; struct tipc_topsrv* topsrv; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct tipc_topsrv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_topsrv_accept ; 
 int tipc_topsrv_create_listener (struct tipc_topsrv*) ; 
 int tipc_topsrv_work_start (struct tipc_topsrv*) ; 
 int /*<<< orphan*/  tipc_topsrv_work_stop (struct tipc_topsrv*) ; 

__attribute__((used)) static int tipc_topsrv_start(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);
	const char name[] = "topology_server";
	struct tipc_topsrv *srv;
	int ret;

	srv = kzalloc(sizeof(*srv), GFP_ATOMIC);
	if (!srv)
		return -ENOMEM;

	srv->net = net;
	INIT_WORK(&srv->awork, tipc_topsrv_accept);

	strscpy(srv->name, name, sizeof(srv->name));
	tn->topsrv = srv;
	atomic_set(&tn->subscription_count, 0);

	spin_lock_init(&srv->idr_lock);
	idr_init(&srv->conn_idr);
	srv->idr_in_use = 0;

	ret = tipc_topsrv_work_start(srv);
	if (ret < 0)
		return ret;

	ret = tipc_topsrv_create_listener(srv);
	if (ret < 0)
		tipc_topsrv_work_stop(srv);

	return ret;
}