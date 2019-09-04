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
struct TYPE_2__ {int heads; int lowsector; unsigned int secspertrack; } ;
struct linux_part {int flags; unsigned int* misc; scalar_t__ checksum; int /*<<< orphan*/  start_cylinder; TYPE_1__ disc_record; } ;
struct grub_acorn_boot_block {int flags; unsigned int* misc; scalar_t__ checksum; int /*<<< orphan*/  start_cylinder; TYPE_1__ disc_record; } ;
typedef  scalar_t__ grub_uint8_t ;
typedef  scalar_t__ grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int GRUB_DISK_SECTOR_SIZE ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_PART_TABLE ; 
 int LINUX_MAP_ENTRIES ; 
 int NONADFS_PARTITION_TYPE_LINUX ; 
 int NONADFS_PARTITION_TYPE_MASK ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct linux_part*) ; 
 scalar_t__ grub_error (int /*<<< orphan*/ ,char*) ; 
 unsigned int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
acorn_partition_map_find (grub_disk_t disk, struct linux_part *m,
			  grub_disk_addr_t *sector)
{
  struct grub_acorn_boot_block boot;
  grub_err_t err;
  unsigned int checksum = 0;
  unsigned int heads;
  unsigned int sectors_per_cylinder;
  int i;

  err = grub_disk_read (disk, 0xC00 / GRUB_DISK_SECTOR_SIZE, 0,
			sizeof (struct grub_acorn_boot_block),
			&boot);
  if (err)
    return err;

  if ((boot.flags & NONADFS_PARTITION_TYPE_MASK) != NONADFS_PARTITION_TYPE_LINUX)
    goto fail;

  for (i = 0; i != 0x1ff; ++i)
    checksum = (checksum & 0xff) + (checksum >> 8) + boot.misc[i];

  if ((grub_uint8_t) checksum != boot.checksum)
    goto fail;

  heads = (boot.disc_record.heads
		    + ((boot.disc_record.lowsector >> 6) & 1));
  sectors_per_cylinder = boot.disc_record.secspertrack * heads;
  *sector = grub_le_to_cpu16 (boot.start_cylinder) * sectors_per_cylinder;

  return grub_disk_read (disk, *sector, 0,
			 sizeof (struct linux_part) * LINUX_MAP_ENTRIES,
			 m);

fail:
  return grub_error (GRUB_ERR_BAD_PART_TABLE,
		     "Linux/ADFS partition map not found");

}