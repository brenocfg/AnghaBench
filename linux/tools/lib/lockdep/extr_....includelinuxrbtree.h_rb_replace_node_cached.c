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
 int /*<<< orphan*/  rb_replace_node (struct rb_node*,struct rb_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rb_replace_node_cached(struct rb_node *victim,
					  struct rb_node *new,
					  struct rb_root_cached *root)
{
	if (root->rb_leftmost == victim)
		root->rb_leftmost = new;
	rb_replace_node(victim, new, &root->rb_root);
}