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
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 

__attribute__((used)) static inline void rb_link_left_of_node(struct rb_node *left, struct rb_node *node)
{
	struct rb_node **p = &node->rb_left;
	while (*p) {
		node = *p;
		p = &node->rb_right;
	}
	rb_link_node(left, node, p);
}