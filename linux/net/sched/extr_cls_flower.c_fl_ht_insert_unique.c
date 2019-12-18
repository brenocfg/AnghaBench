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
struct fl_flow_mask {int /*<<< orphan*/  filter_ht_params; int /*<<< orphan*/  ht; } ;
struct cls_fl_filter {int /*<<< orphan*/  ht_node; struct fl_flow_mask* mask; } ;

/* Variables and functions */
 int EEXIST ; 
 int rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_ht_insert_unique(struct cls_fl_filter *fnew,
			       struct cls_fl_filter *fold,
			       bool *in_ht)
{
	struct fl_flow_mask *mask = fnew->mask;
	int err;

	err = rhashtable_lookup_insert_fast(&mask->ht,
					    &fnew->ht_node,
					    mask->filter_ht_params);
	if (err) {
		*in_ht = false;
		/* It is okay if filter with same key exists when
		 * overwriting.
		 */
		return fold && err == -EEXIST ? 0 : err;
	}

	*in_ht = true;
	return 0;
}