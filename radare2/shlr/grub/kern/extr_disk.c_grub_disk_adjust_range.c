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
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  int grub_off_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int GRUB_DISK_SECTOR_BITS ; 
 int GRUB_DISK_SECTOR_SIZE ; 
 int /*<<< orphan*/  GRUB_ERR_NONE ; 

__attribute__((used)) static grub_err_t
grub_disk_adjust_range (grub_disk_t disk, grub_disk_addr_t *sector,
			grub_off_t *offset, grub_size_t size)
{
  *sector += *offset >> GRUB_DISK_SECTOR_BITS;
  *offset &= GRUB_DISK_SECTOR_SIZE - 1;
/*
  grub_partition_t part;
  for (part = disk->partition; part; part = part->parent)
    {
      grub_disk_addr_t start;
      grub_uint64_t len;

      start = part->start;
      len = part->len;

      if (*sector >= len
	  || len - *sector < ((*offset + size + GRUB_DISK_SECTOR_SIZE - 1)
			      >> GRUB_DISK_SECTOR_BITS))
	return grub_error (GRUB_ERR_OUT_OF_RANGE, "out of partition");

      *sector += start;
    }

  if (disk->total_sectors <= *sector
      || ((*offset + size + GRUB_DISK_SECTOR_SIZE - 1)
	  >> GRUB_DISK_SECTOR_BITS) > disk->total_sectors - *sector)
    return grub_error (GRUB_ERR_OUT_OF_RANGE, "out of disk");
*/
  return GRUB_ERR_NONE;

}