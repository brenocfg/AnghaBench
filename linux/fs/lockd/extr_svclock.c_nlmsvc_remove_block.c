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
struct nlm_block {int /*<<< orphan*/  b_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_blocked_lock ; 
 int /*<<< orphan*/  nlmsvc_release_block (struct nlm_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
nlmsvc_remove_block(struct nlm_block *block)
{
	if (!list_empty(&block->b_list)) {
		spin_lock(&nlm_blocked_lock);
		list_del_init(&block->b_list);
		spin_unlock(&nlm_blocked_lock);
		nlmsvc_release_block(block);
	}
}