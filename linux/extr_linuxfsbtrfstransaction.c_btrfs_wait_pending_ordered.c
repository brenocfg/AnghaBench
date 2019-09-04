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
struct btrfs_transaction {int /*<<< orphan*/  pending_ordered; int /*<<< orphan*/  pending_wait; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
btrfs_wait_pending_ordered(struct btrfs_transaction *cur_trans)
{
	wait_event(cur_trans->pending_wait,
		   atomic_read(&cur_trans->pending_ordered) == 0);
}