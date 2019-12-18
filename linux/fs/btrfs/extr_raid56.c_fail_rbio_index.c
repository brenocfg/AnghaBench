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
struct btrfs_raid_bio {int faila; int failb; int /*<<< orphan*/  bio_list_lock; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fail_rbio_index(struct btrfs_raid_bio *rbio, int failed)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&rbio->bio_list_lock, flags);

	/* we already know this stripe is bad, move on */
	if (rbio->faila == failed || rbio->failb == failed)
		goto out;

	if (rbio->faila == -1) {
		/* first failure on this rbio */
		rbio->faila = failed;
		atomic_inc(&rbio->error);
	} else if (rbio->failb == -1) {
		/* second failure on this rbio */
		rbio->failb = failed;
		atomic_inc(&rbio->error);
	} else {
		ret = -EIO;
	}
out:
	spin_unlock_irqrestore(&rbio->bio_list_lock, flags);

	return ret;
}