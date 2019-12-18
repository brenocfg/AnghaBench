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
struct TYPE_2__ {int /*<<< orphan*/  log2_blksz; } ;
struct grub_ufs_data {int /*<<< orphan*/  disk; int /*<<< orphan*/  be; TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  indir ;
typedef  int /*<<< orphan*/  grub_uint64_t ;
typedef  int grub_uint32_t ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_NOT_IMPLEMENTED_YET ; 
 unsigned int GRUB_UFS_DIRBLKS ; 
 int INODE_BLKSZ ; 
 int INODE_DIRBLOCKS (struct grub_ufs_data*,unsigned int) ; 
 int INODE_INDIRBLOCKS (struct grub_ufs_data*,int) ; 
 int UFS_BLKSZ (struct grub_ufs_data*) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 void* grub_malloc (int) ; 
 int grub_num_to_cpu32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_disk_addr_t
grub_ufs_get_file_block (struct grub_ufs_data *data, unsigned int blk)
{
  int blksz = UFS_BLKSZ (data);
  unsigned int indirsz;
  int log2_blksz;

  /* Direct.  */
  if (blk < GRUB_UFS_DIRBLKS)
    return INODE_DIRBLOCKS (data, blk);

  log2_blksz = grub_num_to_cpu32 (data->sblock.log2_blksz, data->be);

  blk -= GRUB_UFS_DIRBLKS;

  indirsz = blksz / INODE_BLKSZ;
  /* Single indirect block.  */
  if (blk < indirsz)
    {
#ifdef MODE_UFS2
#ifndef _MSC_VER
	  grub_uint64_t indir[blksz / sizeof (grub_uint64_t)];
#else
	  grub_uint64_t *indir = grub_malloc(blksz / sizeof (grub_uint64_t));
#endif
#else
#ifndef _MSC_VER
	  grub_uint32_t indir[blksz / sizeof (grub_uint32_t)];
#else
	  grub_uint32_t *indir = grub_malloc(blksz / sizeof (grub_uint32_t));
#endif
#endif
	  grub_disk_read (data->disk, INODE_INDIRBLOCKS (data, 0) << log2_blksz,
		      0, sizeof (indir), indir);
      return indir[blk];
    }
  blk -= indirsz;

  /* Double indirect block.  */
  if (blk < indirsz * indirsz)
    {
#ifdef MODE_UFS2
#ifndef _MSC_VER
	  grub_uint64_t indir[blksz / sizeof (grub_uint64_t)];
#else
	  grub_uint64_t *indir = grub_malloc(blksz / sizeof (grub_uint64_t));
#endif
#else
#ifndef _MSC_VER
	  grub_uint32_t indir[blksz / sizeof (grub_uint32_t)];
#else
	  grub_uint32_t *indir = grub_malloc(blksz / sizeof (grub_uint32_t));
#endif
#endif

      grub_disk_read (data->disk, INODE_INDIRBLOCKS (data, 1) << log2_blksz,
		      0, sizeof (indir), indir);
      grub_disk_read (data->disk,
		      (indir [blk / indirsz])
		      << log2_blksz,
		      0, sizeof (indir), indir);

      return indir[blk % indirsz];
    }


  grub_error (GRUB_ERR_NOT_IMPLEMENTED_YET,
	      "ufs does not support triple indirect blocks");
  return 0;
}