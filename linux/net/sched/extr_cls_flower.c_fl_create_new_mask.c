#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_4__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_6__ {TYPE_2__ tp_max; TYPE_1__ tp_min; } ;
struct fl_flow_mask {int /*<<< orphan*/  ht; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  filters; TYPE_3__ key; int /*<<< orphan*/  dissector; int /*<<< orphan*/  flags; } ;
struct cls_fl_head {int /*<<< orphan*/  masks_lock; int /*<<< orphan*/  masks; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fl_flow_mask* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCA_FLOWER_MASK_FLAGS_RANGE ; 
 int /*<<< orphan*/  fl_init_dissector (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int fl_init_mask_hashtable (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  fl_mask_copy (struct fl_flow_mask*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  kfree (struct fl_flow_mask*) ; 
 struct fl_flow_mask* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_replace_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fl_flow_mask *fl_create_new_mask(struct cls_fl_head *head,
					       struct fl_flow_mask *mask)
{
	struct fl_flow_mask *newmask;
	int err;

	newmask = kzalloc(sizeof(*newmask), GFP_KERNEL);
	if (!newmask)
		return ERR_PTR(-ENOMEM);

	fl_mask_copy(newmask, mask);

	if ((newmask->key.tp_min.dst && newmask->key.tp_max.dst) ||
	    (newmask->key.tp_min.src && newmask->key.tp_max.src))
		newmask->flags |= TCA_FLOWER_MASK_FLAGS_RANGE;

	err = fl_init_mask_hashtable(newmask);
	if (err)
		goto errout_free;

	fl_init_dissector(&newmask->dissector, &newmask->key);

	INIT_LIST_HEAD_RCU(&newmask->filters);

	refcount_set(&newmask->refcnt, 1);
	err = rhashtable_replace_fast(&head->ht, &mask->ht_node,
				      &newmask->ht_node, mask_ht_params);
	if (err)
		goto errout_destroy;

	spin_lock(&head->masks_lock);
	list_add_tail_rcu(&newmask->list, &head->masks);
	spin_unlock(&head->masks_lock);

	return newmask;

errout_destroy:
	rhashtable_destroy(&newmask->ht);
errout_free:
	kfree(newmask);

	return ERR_PTR(err);
}