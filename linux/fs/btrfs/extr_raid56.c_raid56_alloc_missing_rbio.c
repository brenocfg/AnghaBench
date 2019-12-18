#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_raid_bio {int faila; int generic_bio_cnt; int /*<<< orphan*/  bio_list; int /*<<< orphan*/  operation; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_RBIO_REBUILD_MISSING ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ IS_ERR (struct btrfs_raid_bio*) ; 
 struct btrfs_raid_bio* alloc_rbio (struct btrfs_fs_info*,struct btrfs_bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int find_logical_bio_stripe (struct btrfs_raid_bio*,struct bio*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_raid_bio*) ; 

struct btrfs_raid_bio *
raid56_alloc_missing_rbio(struct btrfs_fs_info *fs_info, struct bio *bio,
			  struct btrfs_bio *bbio, u64 length)
{
	struct btrfs_raid_bio *rbio;

	rbio = alloc_rbio(fs_info, bbio, length);
	if (IS_ERR(rbio))
		return NULL;

	rbio->operation = BTRFS_RBIO_REBUILD_MISSING;
	bio_list_add(&rbio->bio_list, bio);
	/*
	 * This is a special bio which is used to hold the completion handler
	 * and make the scrub rbio is similar to the other types
	 */
	ASSERT(!bio->bi_iter.bi_size);

	rbio->faila = find_logical_bio_stripe(rbio, bio);
	if (rbio->faila == -1) {
		BUG();
		kfree(rbio);
		return NULL;
	}

	/*
	 * When we get bbio, we have already increased bio_counter, record it
	 * so we can free it at rbio_orig_end_io()
	 */
	rbio->generic_bio_cnt = 1;

	return rbio;
}