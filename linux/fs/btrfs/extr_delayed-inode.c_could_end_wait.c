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
struct btrfs_delayed_root {int /*<<< orphan*/  items; int /*<<< orphan*/  items_seq; } ;

/* Variables and functions */
 int BTRFS_DELAYED_BACKGROUND ; 
 int BTRFS_DELAYED_BATCH ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int could_end_wait(struct btrfs_delayed_root *delayed_root, int seq)
{
	int val = atomic_read(&delayed_root->items_seq);

	if (val < seq || val >= seq + BTRFS_DELAYED_BATCH)
		return 1;

	if (atomic_read(&delayed_root->items) < BTRFS_DELAYED_BACKGROUND)
		return 1;

	return 0;
}