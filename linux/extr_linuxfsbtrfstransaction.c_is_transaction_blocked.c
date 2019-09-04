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
struct btrfs_transaction {scalar_t__ state; int /*<<< orphan*/  aborted; } ;

/* Variables and functions */
 scalar_t__ TRANS_STATE_BLOCKED ; 
 scalar_t__ TRANS_STATE_UNBLOCKED ; 

__attribute__((used)) static inline int is_transaction_blocked(struct btrfs_transaction *trans)
{
	return (trans->state >= TRANS_STATE_BLOCKED &&
		trans->state < TRANS_STATE_UNBLOCKED &&
		!trans->aborted);
}