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
struct rb_root_cached {int /*<<< orphan*/  rb_root; struct rb_node* rb_leftmost; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rb_insert_color_cached(struct rb_node *node,
					  struct rb_root_cached *root,
					  bool leftmost)
{
	if (leftmost)
		root->rb_leftmost = node;
	rb_insert_color(node, &root->rb_root);
}