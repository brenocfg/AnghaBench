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
struct btrfs_transaction {int /*<<< orphan*/  num_extwriters; } ;

/* Variables and functions */
 unsigned int TRANS_EXTWRITERS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void extwriter_counter_inc(struct btrfs_transaction *trans,
					 unsigned int type)
{
	if (type & TRANS_EXTWRITERS)
		atomic_inc(&trans->num_extwriters);
}