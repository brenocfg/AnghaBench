#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timerqueue_node {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct timerqueue_head {TYPE_1__ rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase_cached (int /*<<< orphan*/ *,TYPE_1__*) ; 

bool timerqueue_del(struct timerqueue_head *head, struct timerqueue_node *node)
{
	WARN_ON_ONCE(RB_EMPTY_NODE(&node->node));

	rb_erase_cached(&node->node, &head->rb_root);
	RB_CLEAR_NODE(&node->node);

	return !RB_EMPTY_ROOT(&head->rb_root.rb_root);
}