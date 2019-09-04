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
struct rb_root_cached {int /*<<< orphan*/  rb_root; int /*<<< orphan*/  rb_leftmost; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ____rb_erase_color (struct rb_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rb_node* __rb_erase_augmented (struct rb_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_callbacks ; 
 int /*<<< orphan*/  dummy_rotate ; 

void rb_erase_cached(struct rb_node *node, struct rb_root_cached *root)
{
	struct rb_node *rebalance;
	rebalance = __rb_erase_augmented(node, &root->rb_root,
					 &root->rb_leftmost, &dummy_callbacks);
	if (rebalance)
		____rb_erase_color(rebalance, &root->rb_root, dummy_rotate);
}