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
struct fl_flow_key {int dummy; } ;
struct cls_fl_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_key_get_start (struct fl_flow_key*,struct fl_flow_mask*) ; 
 struct cls_fl_filter* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cls_fl_filter *__fl_lookup(struct fl_flow_mask *mask,
					 struct fl_flow_key *mkey)
{
	return rhashtable_lookup_fast(&mask->ht, fl_key_get_start(mkey, mask),
				      mask->filter_ht_params);
}