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
struct scrub_recover {int /*<<< orphan*/  bbio; int /*<<< orphan*/  refs; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_bio_counter_dec (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_put_bbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scrub_recover*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void scrub_put_recover(struct btrfs_fs_info *fs_info,
				     struct scrub_recover *recover)
{
	if (refcount_dec_and_test(&recover->refs)) {
		btrfs_bio_counter_dec(fs_info);
		btrfs_put_bbio(recover->bbio);
		kfree(recover);
	}
}