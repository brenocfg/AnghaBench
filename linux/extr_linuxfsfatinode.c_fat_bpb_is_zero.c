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
struct fat_boot_sector {scalar_t__ heads; scalar_t__ secs_track; scalar_t__ fat_length; scalar_t__ media; int /*<<< orphan*/  sectors; int /*<<< orphan*/  dir_entries; scalar_t__ fats; scalar_t__ reserved; scalar_t__ sec_per_clus; int /*<<< orphan*/  sector_size; } ;

/* Variables and functions */
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fat_bpb_is_zero(struct fat_boot_sector *b)
{
	if (get_unaligned_le16(&b->sector_size))
		return false;
	if (b->sec_per_clus)
		return false;
	if (b->reserved)
		return false;
	if (b->fats)
		return false;
	if (get_unaligned_le16(&b->dir_entries))
		return false;
	if (get_unaligned_le16(&b->sectors))
		return false;
	if (b->media)
		return false;
	if (b->fat_length)
		return false;
	if (b->secs_track)
		return false;
	if (b->heads)
		return false;
	return true;
}