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
struct fl_flow_mask {int /*<<< orphan*/  ht_node; int /*<<< orphan*/  refcnt; } ;
struct cls_fl_head {int /*<<< orphan*/  ht; } ;
struct cls_fl_filter {struct fl_flow_mask* mask; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct fl_flow_mask*) ; 
 int PTR_ERR (struct fl_flow_mask*) ; 
 struct fl_flow_mask* fl_create_new_mask (struct cls_fl_head*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct fl_flow_mask* rhashtable_lookup_get_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_check_assign_mask(struct cls_fl_head *head,
				struct cls_fl_filter *fnew,
				struct cls_fl_filter *fold,
				struct fl_flow_mask *mask)
{
	struct fl_flow_mask *newmask;
	int ret = 0;

	rcu_read_lock();

	/* Insert mask as temporary node to prevent concurrent creation of mask
	 * with same key. Any concurrent lookups with same key will return
	 * -EAGAIN because mask's refcnt is zero.
	 */
	fnew->mask = rhashtable_lookup_get_insert_fast(&head->ht,
						       &mask->ht_node,
						       mask_ht_params);
	if (!fnew->mask) {
		rcu_read_unlock();

		if (fold) {
			ret = -EINVAL;
			goto errout_cleanup;
		}

		newmask = fl_create_new_mask(head, mask);
		if (IS_ERR(newmask)) {
			ret = PTR_ERR(newmask);
			goto errout_cleanup;
		}

		fnew->mask = newmask;
		return 0;
	} else if (IS_ERR(fnew->mask)) {
		ret = PTR_ERR(fnew->mask);
	} else if (fold && fold->mask != fnew->mask) {
		ret = -EINVAL;
	} else if (!refcount_inc_not_zero(&fnew->mask->refcnt)) {
		/* Mask was deleted concurrently, try again */
		ret = -EAGAIN;
	}
	rcu_read_unlock();
	return ret;

errout_cleanup:
	rhashtable_remove_fast(&head->ht, &mask->ht_node,
			       mask_ht_params);
	return ret;
}