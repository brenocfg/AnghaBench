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
struct backing_dev_info {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 scalar_t__ bdi_init (struct backing_dev_info*) ; 
 int /*<<< orphan*/  kfree (struct backing_dev_info*) ; 
 struct backing_dev_info* kmalloc_node (int,int,int) ; 

struct backing_dev_info *bdi_alloc_node(gfp_t gfp_mask, int node_id)
{
	struct backing_dev_info *bdi;

	bdi = kmalloc_node(sizeof(struct backing_dev_info),
			   gfp_mask | __GFP_ZERO, node_id);
	if (!bdi)
		return NULL;

	if (bdi_init(bdi)) {
		kfree(bdi);
		return NULL;
	}
	return bdi;
}