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
struct TYPE_2__ {int /*<<< orphan*/  sr_dat; } ;
struct grub_nilfs2_data {TYPE_1__ sroot; int /*<<< orphan*/  disk; } ;
struct grub_nilfs2_dat_entry {int /*<<< orphan*/  de_blocknr; } ;
typedef  int grub_uint64_t ;
typedef  int /*<<< orphan*/  grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int LOG2_NILFS2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 
 int /*<<< orphan*/  NILFS2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct grub_nilfs2_dat_entry*) ; 
 int /*<<< orphan*/  grub_divmod64 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 int grub_nilfs2_bmap_lookup (struct grub_nilfs2_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_nilfs2_palloc_entry_offset (struct grub_nilfs2_data*,int,int) ; 

__attribute__((used)) static grub_uint64_t
grub_nilfs2_dat_translate (struct grub_nilfs2_data *data, grub_uint64_t key)
{
  struct grub_nilfs2_dat_entry entry;
  grub_disk_t disk = data->disk;
  grub_uint64_t pptr;
  grub_uint32_t blockno, offset;
  unsigned int nilfs2_block_count = (1 << LOG2_NILFS2_BLOCK_SIZE (data));

  blockno = grub_nilfs2_palloc_entry_offset (data, key,
					     sizeof (struct
						     grub_nilfs2_dat_entry));

  grub_divmod64 (key * sizeof (struct grub_nilfs2_dat_entry),
		 NILFS2_BLOCK_SIZE (data), &offset);

  pptr = grub_nilfs2_bmap_lookup (data, &data->sroot.sr_dat, blockno, 0);
  if (pptr == (grub_uint64_t) - 1)
    {
      grub_error (GRUB_ERR_BAD_FS, "btree lookup failure");
      return -1;
    }

  grub_disk_read (disk, pptr * nilfs2_block_count, offset,
		  sizeof (struct grub_nilfs2_dat_entry), &entry);

  return grub_le_to_cpu64 (entry.de_blocknr);
}