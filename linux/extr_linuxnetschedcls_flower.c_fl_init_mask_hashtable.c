#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key_offset; int /*<<< orphan*/  key_len; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct fl_flow_mask {TYPE_2__ filter_ht_params; int /*<<< orphan*/  ht; TYPE_1__ range; } ;

/* Variables and functions */
 TYPE_2__ fl_ht_params ; 
 int /*<<< orphan*/  fl_mask_range (struct fl_flow_mask*) ; 
 int rhashtable_init (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int fl_init_mask_hashtable(struct fl_flow_mask *mask)
{
	mask->filter_ht_params = fl_ht_params;
	mask->filter_ht_params.key_len = fl_mask_range(mask);
	mask->filter_ht_params.key_offset += mask->range.start;

	return rhashtable_init(&mask->ht, &mask->filter_ht_params);
}