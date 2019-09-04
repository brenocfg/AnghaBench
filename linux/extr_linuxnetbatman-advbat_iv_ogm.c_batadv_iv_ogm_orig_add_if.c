#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ogm_cnt_lock; void* bcast_own_sum; void* bcast_own; } ;
struct batadv_orig_node {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 unsigned int BATADV_NUM_WORDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int batadv_iv_ogm_orig_add_if(struct batadv_orig_node *orig_node,
				     unsigned int max_if_num)
{
	void *data_ptr;
	size_t old_size;
	int ret = -ENOMEM;

	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	old_size = (max_if_num - 1) * sizeof(unsigned long) * BATADV_NUM_WORDS;
	data_ptr = kmalloc_array(max_if_num,
				 BATADV_NUM_WORDS * sizeof(unsigned long),
				 GFP_ATOMIC);
	if (!data_ptr)
		goto unlock;

	memcpy(data_ptr, orig_node->bat_iv.bcast_own, old_size);
	kfree(orig_node->bat_iv.bcast_own);
	orig_node->bat_iv.bcast_own = data_ptr;

	data_ptr = kmalloc_array(max_if_num, sizeof(u8), GFP_ATOMIC);
	if (!data_ptr)
		goto unlock;

	memcpy(data_ptr, orig_node->bat_iv.bcast_own_sum,
	       (max_if_num - 1) * sizeof(u8));
	kfree(orig_node->bat_iv.bcast_own_sum);
	orig_node->bat_iv.bcast_own_sum = data_ptr;

	ret = 0;

unlock:
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	return ret;
}