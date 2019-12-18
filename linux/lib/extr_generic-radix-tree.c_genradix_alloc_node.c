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
struct genradix_node {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  kmemleak_alloc (struct genradix_node*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline struct genradix_node *genradix_alloc_node(gfp_t gfp_mask)
{
	struct genradix_node *node;

	node = (struct genradix_node *)__get_free_page(gfp_mask|__GFP_ZERO);

	/*
	 * We're using pages (not slab allocations) directly for kernel data
	 * structures, so we need to explicitly inform kmemleak of them in order
	 * to avoid false positive memory leak reports.
	 */
	kmemleak_alloc(node, PAGE_SIZE, 1, gfp_mask);
	return node;
}