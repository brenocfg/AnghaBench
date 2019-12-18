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
struct test_node {int /*<<< orphan*/  rb; } ;
struct rb_root_cached {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,struct rb_root_cached*) ; 

__attribute__((used)) static inline void erase_cached(struct test_node *node, struct rb_root_cached *root)
{
	rb_erase_cached(&node->rb, root);
}