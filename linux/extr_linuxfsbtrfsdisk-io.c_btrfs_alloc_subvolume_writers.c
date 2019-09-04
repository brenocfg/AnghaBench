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
struct btrfs_subvolume_writers {int /*<<< orphan*/  wait; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct btrfs_subvolume_writers* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_subvolume_writers*) ; 
 struct btrfs_subvolume_writers* kmalloc (int,int /*<<< orphan*/ ) ; 
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct btrfs_subvolume_writers *btrfs_alloc_subvolume_writers(void)
{
	struct btrfs_subvolume_writers *writers;
	int ret;

	writers = kmalloc(sizeof(*writers), GFP_NOFS);
	if (!writers)
		return ERR_PTR(-ENOMEM);

	ret = percpu_counter_init(&writers->counter, 0, GFP_NOFS);
	if (ret < 0) {
		kfree(writers);
		return ERR_PTR(ret);
	}

	init_waitqueue_head(&writers->wait);
	return writers;
}