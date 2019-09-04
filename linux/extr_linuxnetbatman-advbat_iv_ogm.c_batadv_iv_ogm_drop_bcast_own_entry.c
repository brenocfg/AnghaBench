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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {void* bcast_own; int /*<<< orphan*/  ogm_cnt_lock; } ;
struct batadv_orig_node {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 int BATADV_NUM_WORDS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_array (unsigned int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,void*,unsigned int) ; 

__attribute__((used)) static void
batadv_iv_ogm_drop_bcast_own_entry(struct batadv_orig_node *orig_node,
				   unsigned int max_if_num,
				   unsigned int del_if_num)
{
	size_t chunk_size;
	size_t if_offset;
	void *data_ptr;

	lockdep_assert_held(&orig_node->bat_iv.ogm_cnt_lock);

	chunk_size = sizeof(unsigned long) * BATADV_NUM_WORDS;
	data_ptr = kmalloc_array(max_if_num, chunk_size, GFP_ATOMIC);
	if (!data_ptr)
		/* use old buffer when new one could not be allocated */
		data_ptr = orig_node->bat_iv.bcast_own;

	/* copy first part */
	memmove(data_ptr, orig_node->bat_iv.bcast_own, del_if_num * chunk_size);

	/* copy second part */
	if_offset = (del_if_num + 1) * chunk_size;
	memmove((char *)data_ptr + del_if_num * chunk_size,
		(uint8_t *)orig_node->bat_iv.bcast_own + if_offset,
		(max_if_num - del_if_num) * chunk_size);

	/* bcast_own was shrunk down in new buffer; free old one */
	if (orig_node->bat_iv.bcast_own != data_ptr) {
		kfree(orig_node->bat_iv.bcast_own);
		orig_node->bat_iv.bcast_own = data_ptr;
	}
}