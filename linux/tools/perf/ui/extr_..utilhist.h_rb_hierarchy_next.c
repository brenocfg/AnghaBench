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
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMD_NORMAL ; 
 struct rb_node* __rb_hierarchy_next (struct rb_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rb_node *rb_hierarchy_next(struct rb_node *node)
{
	return __rb_hierarchy_next(node, HMD_NORMAL);
}