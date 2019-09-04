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
struct fl_flow_mask {int /*<<< orphan*/  ht; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  filters; int /*<<< orphan*/  key; int /*<<< orphan*/  dissector; } ;
struct cls_fl_head {int /*<<< orphan*/  masks; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fl_flow_mask* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fl_init_dissector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fl_init_mask_hashtable (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  fl_mask_copy (struct fl_flow_mask*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  kfree (struct fl_flow_mask*) ; 
 struct fl_flow_mask* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fl_flow_mask *fl_create_new_mask(struct cls_fl_head *head,
					       struct fl_flow_mask *mask)
{
	struct fl_flow_mask *newmask;
	int err;

	newmask = kzalloc(sizeof(*newmask), GFP_KERNEL);
	if (!newmask)
		return ERR_PTR(-ENOMEM);

	fl_mask_copy(newmask, mask);

	err = fl_init_mask_hashtable(newmask);
	if (err)
		goto errout_free;

	fl_init_dissector(&newmask->dissector, &newmask->key);

	INIT_LIST_HEAD_RCU(&newmask->filters);

	err = rhashtable_insert_fast(&head->ht, &newmask->ht_node,
				     mask_ht_params);
	if (err)
		goto errout_destroy;

	list_add_tail_rcu(&newmask->list, &head->masks);

	return newmask;

errout_destroy:
	rhashtable_destroy(&newmask->ht);
errout_free:
	kfree(newmask);

	return ERR_PTR(err);
}