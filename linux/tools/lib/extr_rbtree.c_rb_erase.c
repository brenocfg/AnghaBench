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
struct rb_root {int dummy; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ____rb_erase_color (struct rb_node*,struct rb_root*,int /*<<< orphan*/ ) ; 
 struct rb_node* __rb_erase_augmented (struct rb_node*,struct rb_root*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_callbacks ; 
 int /*<<< orphan*/  dummy_rotate ; 

void rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *rebalance;
	rebalance = __rb_erase_augmented(node, root, &dummy_callbacks);
	if (rebalance)
		____rb_erase_color(rebalance, root, dummy_rotate);
}