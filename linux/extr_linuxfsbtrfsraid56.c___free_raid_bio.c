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
struct btrfs_raid_bio {int nr_pages; int /*<<< orphan*/  bbio; int /*<<< orphan*/ ** stripe_pages; int /*<<< orphan*/  bio_list; int /*<<< orphan*/  hash_list; int /*<<< orphan*/  stripe_cache; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_put_bbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __free_raid_bio(struct btrfs_raid_bio *rbio)
{
	int i;

	if (!refcount_dec_and_test(&rbio->refs))
		return;

	WARN_ON(!list_empty(&rbio->stripe_cache));
	WARN_ON(!list_empty(&rbio->hash_list));
	WARN_ON(!bio_list_empty(&rbio->bio_list));

	for (i = 0; i < rbio->nr_pages; i++) {
		if (rbio->stripe_pages[i]) {
			__free_page(rbio->stripe_pages[i]);
			rbio->stripe_pages[i] = NULL;
		}
	}

	btrfs_put_bbio(rbio->bbio);
	kfree(rbio);
}