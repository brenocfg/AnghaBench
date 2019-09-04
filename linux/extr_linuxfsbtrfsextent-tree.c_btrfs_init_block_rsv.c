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
struct btrfs_block_rsv {unsigned short type; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct btrfs_block_rsv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void btrfs_init_block_rsv(struct btrfs_block_rsv *rsv, unsigned short type)
{
	memset(rsv, 0, sizeof(*rsv));
	spin_lock_init(&rsv->lock);
	rsv->type = type;
}