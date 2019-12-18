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
struct fl_flow_mask {int /*<<< orphan*/  rwork; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  refcnt; } ;
struct cls_fl_head {int /*<<< orphan*/  masks_lock; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_mask_free_work ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fl_mask_put(struct cls_fl_head *head, struct fl_flow_mask *mask)
{
	if (!refcount_dec_and_test(&mask->refcnt))
		return false;

	rhashtable_remove_fast(&head->ht, &mask->ht_node, mask_ht_params);

	spin_lock(&head->masks_lock);
	list_del_rcu(&mask->list);
	spin_unlock(&head->masks_lock);

	tcf_queue_work(&mask->rwork, fl_mask_free_work);

	return true;
}