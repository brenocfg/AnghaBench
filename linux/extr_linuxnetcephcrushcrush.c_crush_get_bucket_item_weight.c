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
struct crush_bucket_uniform {int item_weight; } ;
struct crush_bucket_tree {int* node_weights; } ;
struct crush_bucket_straw2 {int* item_weights; } ;
struct crush_bucket_straw {int* item_weights; } ;
struct crush_bucket_list {int* item_weights; } ;
struct crush_bucket {scalar_t__ size; int alg; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
#define  CRUSH_BUCKET_LIST 132 
#define  CRUSH_BUCKET_STRAW 131 
#define  CRUSH_BUCKET_STRAW2 130 
#define  CRUSH_BUCKET_TREE 129 
#define  CRUSH_BUCKET_UNIFORM 128 
 size_t crush_calc_tree_node (int) ; 

int crush_get_bucket_item_weight(const struct crush_bucket *b, int p)
{
	if ((__u32)p >= b->size)
		return 0;

	switch (b->alg) {
	case CRUSH_BUCKET_UNIFORM:
		return ((struct crush_bucket_uniform *)b)->item_weight;
	case CRUSH_BUCKET_LIST:
		return ((struct crush_bucket_list *)b)->item_weights[p];
	case CRUSH_BUCKET_TREE:
		return ((struct crush_bucket_tree *)b)->node_weights[crush_calc_tree_node(p)];
	case CRUSH_BUCKET_STRAW:
		return ((struct crush_bucket_straw *)b)->item_weights[p];
	case CRUSH_BUCKET_STRAW2:
		return ((struct crush_bucket_straw2 *)b)->item_weights[p];
	}
	return 0;
}