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
struct btrfs_root {int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  log_writers; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 

void btrfs_end_log_trans(struct btrfs_root *root)
{
	if (atomic_dec_and_test(&root->log_writers)) {
		/* atomic_dec_and_test implies a barrier */
		cond_wake_up_nomb(&root->log_writer_wait);
	}
}