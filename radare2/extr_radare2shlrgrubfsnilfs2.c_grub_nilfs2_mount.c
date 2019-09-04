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
struct grub_nilfs2_super_root {int dummy; } ;
struct grub_nilfs2_super_block {int dummy; } ;
struct grub_nilfs2_segment_summary {int /*<<< orphan*/  ss_nblocks; int /*<<< orphan*/  s_last_pseg; } ;
struct grub_nilfs2_inode {int dummy; } ;
struct TYPE_2__ {int ino; int inode_read; int /*<<< orphan*/  inode; struct grub_nilfs2_data* data; } ;
struct grub_nilfs2_data {int /*<<< orphan*/ * inode; TYPE_1__ diropen; int /*<<< orphan*/  ifile; int /*<<< orphan*/  disk; struct grub_nilfs2_segment_summary sroot; struct grub_nilfs2_segment_summary sblock; } ;
struct grub_nilfs2_checkpoint {int /*<<< orphan*/  cp_ifile_inode; } ;
typedef  unsigned int grub_uint64_t ;
typedef  int grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ GRUB_ERR_OUT_OF_RANGE ; 
 int LOG2_NILFS2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,struct grub_nilfs2_segment_summary*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_nilfs2_data*) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 unsigned int grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 struct grub_nilfs2_data* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  grub_nilfs2_read_inode (struct grub_nilfs2_data*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_nilfs2_read_last_checkpoint (struct grub_nilfs2_data*,struct grub_nilfs2_checkpoint*) ; 
 int /*<<< orphan*/  grub_nilfs2_valid_sb (struct grub_nilfs2_segment_summary*) ; 

__attribute__((used)) static struct grub_nilfs2_data *
grub_nilfs2_mount (grub_disk_t disk)
{
  struct grub_nilfs2_data *data;
  struct grub_nilfs2_segment_summary ss;
  struct grub_nilfs2_checkpoint last_checkpoint;
  grub_uint64_t last_pseg;
  grub_uint32_t nblocks;
  unsigned int nilfs2_block_count;

  data = grub_malloc (sizeof (struct grub_nilfs2_data));
  if (!data)
    return 0;

  /* Read the superblock.  */
  grub_disk_read (disk, 1 * 2, 0, sizeof (struct grub_nilfs2_super_block),
		  &data->sblock);
  if (grub_errno)
    goto fail;

  /* Make sure this is an nilfs2 filesystem.  */
  if (!grub_nilfs2_valid_sb (&data->sblock))
    {
      grub_error (GRUB_ERR_BAD_FS, "not a nilfs2 filesystem");
      goto fail;
    }

  nilfs2_block_count = (1 << LOG2_NILFS2_BLOCK_SIZE (data));

  /* Read the last segment summary. */
  last_pseg = grub_le_to_cpu64 (data->sblock.s_last_pseg);
  grub_disk_read (disk, last_pseg * nilfs2_block_count, 0,
		  sizeof (struct grub_nilfs2_segment_summary), &ss);

  if (grub_errno)
    goto fail;

  /* Read the super root block. */
  nblocks = grub_le_to_cpu32 (ss.ss_nblocks);
  grub_disk_read (disk, (last_pseg + (nblocks - 1)) * nilfs2_block_count, 0,
		  sizeof (struct grub_nilfs2_super_root), &data->sroot);

  if (grub_errno)
    goto fail;

  data->disk = disk;

  grub_nilfs2_read_last_checkpoint (data, &last_checkpoint);

  if (grub_errno)
    goto fail;

  grub_memcpy (&data->ifile, &last_checkpoint.cp_ifile_inode,
	       sizeof (struct grub_nilfs2_inode));

  data->diropen.data = data;
  data->diropen.ino = 2;
  data->diropen.inode_read = 1;
  data->inode = &data->diropen.inode;

  grub_nilfs2_read_inode (data, 2, data->inode);

  return data;

fail:
  if (grub_errno == GRUB_ERR_OUT_OF_RANGE)
    grub_error (GRUB_ERR_BAD_FS, "not a nilfs2 filesystem");

  grub_free (data);
  return 0;
}