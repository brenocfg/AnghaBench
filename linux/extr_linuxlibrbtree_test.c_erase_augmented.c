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
struct rb_root_cached {int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  augment_callbacks ; 
 int /*<<< orphan*/  rb_erase_augmented (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void erase_augmented(struct test_node *node, struct rb_root_cached *root)
{
	rb_erase_augmented(&node->rb, &root->rb_root, &augment_callbacks);
}