#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scrub_page {int logical; TYPE_3__* recover; TYPE_2__* sblock; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_8__ {int bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/ * bi_private; TYPE_4__ bi_iter; } ;
struct TYPE_7__ {int /*<<< orphan*/  map_length; int /*<<< orphan*/  bbio; } ;
struct TYPE_6__ {TYPE_1__** pagev; } ;
struct TYPE_5__ {int mirror_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int raid56_parity_recover (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scrub_bio_wait_endio ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scrub_submit_raid56_bio_wait(struct btrfs_fs_info *fs_info,
					struct bio *bio,
					struct scrub_page *page)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int ret;
	int mirror_num;

	bio->bi_iter.bi_sector = page->logical >> 9;
	bio->bi_private = &done;
	bio->bi_end_io = scrub_bio_wait_endio;

	mirror_num = page->sblock->pagev[0]->mirror_num;
	ret = raid56_parity_recover(fs_info, bio, page->recover->bbio,
				    page->recover->map_length,
				    mirror_num, 0);
	if (ret)
		return ret;

	wait_for_completion_io(&done);
	return blk_status_to_errno(bio->bi_status);
}