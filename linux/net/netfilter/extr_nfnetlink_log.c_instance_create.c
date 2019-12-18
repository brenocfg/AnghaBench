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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u32 ;
struct user_namespace {int dummy; } ;
struct nfulnl_instance {int /*<<< orphan*/  hlist; int /*<<< orphan*/  copy_range; int /*<<< orphan*/  copy_mode; int /*<<< orphan*/  nlbufsiz; int /*<<< orphan*/  flushtimeout; int /*<<< orphan*/  qthreshold; int /*<<< orphan*/  group_num; int /*<<< orphan*/  peer_portid; struct user_namespace* peer_user_ns; int /*<<< orphan*/  net; int /*<<< orphan*/  timer; int /*<<< orphan*/  use; int /*<<< orphan*/  lock; } ;
struct nfnl_log_net {int /*<<< orphan*/  instances_lock; int /*<<< orphan*/ * instance_table; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct nfulnl_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFULNL_COPY_PACKET ; 
 int /*<<< orphan*/  NFULNL_COPY_RANGE_MAX ; 
 int /*<<< orphan*/  NFULNL_NLBUFSIZ_DEFAULT ; 
 int /*<<< orphan*/  NFULNL_QTHRESH_DEFAULT ; 
 int /*<<< orphan*/  NFULNL_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ __instance_lookup (struct nfnl_log_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t instance_hashfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfulnl_instance*) ; 
 struct nfulnl_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nfnl_log_net* nfnl_log_pernet (struct net*) ; 
 int /*<<< orphan*/  nfulnl_timer ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfulnl_instance *
instance_create(struct net *net, u_int16_t group_num,
		u32 portid, struct user_namespace *user_ns)
{
	struct nfulnl_instance *inst;
	struct nfnl_log_net *log = nfnl_log_pernet(net);
	int err;

	spin_lock_bh(&log->instances_lock);
	if (__instance_lookup(log, group_num)) {
		err = -EEXIST;
		goto out_unlock;
	}

	inst = kzalloc(sizeof(*inst), GFP_ATOMIC);
	if (!inst) {
		err = -ENOMEM;
		goto out_unlock;
	}

	if (!try_module_get(THIS_MODULE)) {
		kfree(inst);
		err = -EAGAIN;
		goto out_unlock;
	}

	INIT_HLIST_NODE(&inst->hlist);
	spin_lock_init(&inst->lock);
	/* needs to be two, since we _put() after creation */
	refcount_set(&inst->use, 2);

	timer_setup(&inst->timer, nfulnl_timer, 0);

	inst->net = get_net(net);
	inst->peer_user_ns = user_ns;
	inst->peer_portid = portid;
	inst->group_num = group_num;

	inst->qthreshold 	= NFULNL_QTHRESH_DEFAULT;
	inst->flushtimeout 	= NFULNL_TIMEOUT_DEFAULT;
	inst->nlbufsiz 		= NFULNL_NLBUFSIZ_DEFAULT;
	inst->copy_mode 	= NFULNL_COPY_PACKET;
	inst->copy_range 	= NFULNL_COPY_RANGE_MAX;

	hlist_add_head_rcu(&inst->hlist,
		       &log->instance_table[instance_hashfn(group_num)]);


	spin_unlock_bh(&log->instances_lock);

	return inst;

out_unlock:
	spin_unlock_bh(&log->instances_lock);
	return ERR_PTR(err);
}