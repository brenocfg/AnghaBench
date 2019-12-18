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

/* Variables and functions */
 int /*<<< orphan*/  MAX_IDX ; 
 int /*<<< orphan*/  NEW_TAG ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  tag_tagged_items (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_complete ; 

__attribute__((used)) static void *tag_entries_fn(void *arg)
{
	rcu_register_thread();

	while (!test_complete) {
		tag_tagged_items(&array, 0, MAX_IDX, 10, TAG, NEW_TAG);
	}
	rcu_unregister_thread();
	return NULL;
}