#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_bdev; } ;
struct ext4_fsmap {scalar_t__ fmr_device; } ;
struct TYPE_6__ {TYPE_2__* journal_bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ new_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ext4_getfsmap_is_valid_device(struct super_block *sb,
					  struct ext4_fsmap *fm)
{
	if (fm->fmr_device == 0 || fm->fmr_device == UINT_MAX ||
	    fm->fmr_device == new_encode_dev(sb->s_bdev->bd_dev))
		return true;
	if (EXT4_SB(sb)->journal_bdev &&
	    fm->fmr_device == new_encode_dev(EXT4_SB(sb)->journal_bdev->bd_dev))
		return true;
	return false;
}