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
struct nfqnl_instance {int /*<<< orphan*/  hlist; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  copy_mode; int /*<<< orphan*/  copy_range; int /*<<< orphan*/  queue_maxlen; int /*<<< orphan*/  peer_portid; int /*<<< orphan*/  queue_num; } ;
struct nfnl_queue_net {int /*<<< orphan*/  instances_lock; int /*<<< orphan*/ * instance_table; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct nfqnl_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFQNL_COPY_NONE ; 
 int /*<<< orphan*/  NFQNL_MAX_COPY_RANGE ; 
 int /*<<< orphan*/  NFQNL_QMAX_DEFAULT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int instance_hashfn (int /*<<< orphan*/ ) ; 
 scalar_t__ instance_lookup (struct nfnl_queue_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfqnl_instance*) ; 
 struct nfqnl_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfqnl_instance *
instance_create(struct nfnl_queue_net *q, u_int16_t queue_num, u32 portid)
{
	struct nfqnl_instance *inst;
	unsigned int h;
	int err;

	spin_lock(&q->instances_lock);
	if (instance_lookup(q, queue_num)) {
		err = -EEXIST;
		goto out_unlock;
	}

	inst = kzalloc(sizeof(*inst), GFP_ATOMIC);
	if (!inst) {
		err = -ENOMEM;
		goto out_unlock;
	}

	inst->queue_num = queue_num;
	inst->peer_portid = portid;
	inst->queue_maxlen = NFQNL_QMAX_DEFAULT;
	inst->copy_range = NFQNL_MAX_COPY_RANGE;
	inst->copy_mode = NFQNL_COPY_NONE;
	spin_lock_init(&inst->lock);
	INIT_LIST_HEAD(&inst->queue_list);

	if (!try_module_get(THIS_MODULE)) {
		err = -EAGAIN;
		goto out_free;
	}

	h = instance_hashfn(queue_num);
	hlist_add_head_rcu(&inst->hlist, &q->instance_table[h]);

	spin_unlock(&q->instances_lock);

	return inst;

out_free:
	kfree(inst);
out_unlock:
	spin_unlock(&q->instances_lock);
	return ERR_PTR(err);
}