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
struct fl_flow_mask {int dummy; } ;
struct cls_fl_head {int /*<<< orphan*/  ht; } ;
struct cls_fl_filter {struct fl_flow_mask* mask; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct fl_flow_mask*) ; 
 int PTR_ERR (struct fl_flow_mask*) ; 
 struct fl_flow_mask* fl_create_new_mask (struct cls_fl_head*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  mask_ht_params ; 
 struct fl_flow_mask* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct fl_flow_mask*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_check_assign_mask(struct cls_fl_head *head,
				struct cls_fl_filter *fnew,
				struct cls_fl_filter *fold,
				struct fl_flow_mask *mask)
{
	struct fl_flow_mask *newmask;

	fnew->mask = rhashtable_lookup_fast(&head->ht, mask, mask_ht_params);
	if (!fnew->mask) {
		if (fold)
			return -EINVAL;

		newmask = fl_create_new_mask(head, mask);
		if (IS_ERR(newmask))
			return PTR_ERR(newmask);

		fnew->mask = newmask;
	} else if (fold && fold->mask != fnew->mask) {
		return -EINVAL;
	}

	return 0;
}