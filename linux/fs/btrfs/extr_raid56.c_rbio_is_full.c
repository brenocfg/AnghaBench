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
struct btrfs_raid_bio {unsigned long bio_list_bytes; unsigned long nr_data; unsigned long stripe_len; int /*<<< orphan*/  bio_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rbio_is_full(struct btrfs_raid_bio *rbio)
{
	unsigned long flags;
	unsigned long size = rbio->bio_list_bytes;
	int ret = 1;

	spin_lock_irqsave(&rbio->bio_list_lock, flags);
	if (size != rbio->nr_data * rbio->stripe_len)
		ret = 0;
	BUG_ON(size > rbio->nr_data * rbio->stripe_len);
	spin_unlock_irqrestore(&rbio->bio_list_lock, flags);

	return ret;
}