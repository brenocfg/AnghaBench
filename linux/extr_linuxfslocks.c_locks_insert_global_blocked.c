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
struct file_lock {int /*<<< orphan*/  fl_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocked_hash ; 
 int /*<<< orphan*/  blocked_lock_lock ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_owner_key (struct file_lock*) ; 

__attribute__((used)) static void locks_insert_global_blocked(struct file_lock *waiter)
{
	lockdep_assert_held(&blocked_lock_lock);

	hash_add(blocked_hash, &waiter->fl_link, posix_owner_key(waiter));
}