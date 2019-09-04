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
struct btrfs_dev_replace {int /*<<< orphan*/  read_locks; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 

void btrfs_dev_replace_read_lock(struct btrfs_dev_replace *dev_replace)
{
	read_lock(&dev_replace->lock);
	atomic_inc(&dev_replace->read_locks);
}