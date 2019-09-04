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
struct super_block {int s_blocksize_bits; } ;
struct fsmap {int fmr_physical; int fmr_length; int /*<<< orphan*/  fmr_owner; int /*<<< orphan*/  fmr_flags; int /*<<< orphan*/  fmr_device; } ;
struct ext4_fsmap {int fmr_physical; int fmr_length; int /*<<< orphan*/  fmr_owner; int /*<<< orphan*/  fmr_flags; int /*<<< orphan*/  fmr_device; } ;

/* Variables and functions */

void ext4_fsmap_to_internal(struct super_block *sb, struct ext4_fsmap *dest,
			    struct fsmap *src)
{
	dest->fmr_device = src->fmr_device;
	dest->fmr_flags = src->fmr_flags;
	dest->fmr_physical = src->fmr_physical >> sb->s_blocksize_bits;
	dest->fmr_owner = src->fmr_owner;
	dest->fmr_length = src->fmr_length >> sb->s_blocksize_bits;
}