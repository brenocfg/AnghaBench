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
struct btrfs_raid_bio {int /*<<< orphan*/  bio_list; scalar_t__ generic_bio_cnt; scalar_t__ bio_list_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void merge_rbio(struct btrfs_raid_bio *dest,
		       struct btrfs_raid_bio *victim)
{
	bio_list_merge(&dest->bio_list, &victim->bio_list);
	dest->bio_list_bytes += victim->bio_list_bytes;
	dest->generic_bio_cnt += victim->generic_bio_cnt;
	bio_list_init(&victim->bio_list);
}