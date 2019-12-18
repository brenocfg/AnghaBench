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
struct rtree_node {int /*<<< orphan*/  list; int /*<<< orphan*/  data; } ;
struct list_head {int dummy; } ;
struct chain_allocator {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct rtree_node* chain_alloc (struct chain_allocator*,int) ; 
 int /*<<< orphan*/  get_image_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static struct rtree_node *alloc_rtree_node(gfp_t gfp_mask, int safe_needed,
					   struct chain_allocator *ca,
					   struct list_head *list)
{
	struct rtree_node *node;

	node = chain_alloc(ca, sizeof(struct rtree_node));
	if (!node)
		return NULL;

	node->data = get_image_page(gfp_mask, safe_needed);
	if (!node->data)
		return NULL;

	list_add_tail(&node->list, list);

	return node;
}