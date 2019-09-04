#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct grub_hfs_extent_key {void* first_block; int /*<<< orphan*/  fileid; scalar_t__ forktype; } ;
struct TYPE_6__ {int /*<<< orphan*/  first_block; } ;
struct grub_hfs_data {int /*<<< orphan*/  ext_root; TYPE_1__ sblock; } ;
typedef  TYPE_2__* grub_hfs_datarecord_t ;
typedef  int /*<<< orphan*/  dr ;
typedef  int /*<<< orphan*/  cache_dr ;
struct TYPE_7__ {int /*<<< orphan*/  count; int /*<<< orphan*/  first_block; } ;

/* Variables and functions */
 int GRUB_HFS_BLKS ; 
 int grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 void* grub_cpu_to_be16 (int) ; 
 int /*<<< orphan*/  grub_cpu_to_be32 (int) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_hfs_find_node (struct grub_hfs_data*,char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  grub_memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static unsigned int
grub_hfs_block (struct grub_hfs_data *data, grub_hfs_datarecord_t dat,
		int file, int block, int cache)
{
  grub_hfs_datarecord_t dr;
  int pos = 0;
  struct grub_hfs_extent_key key;

  int tree = 0;
  static int cache_file = 0;
  static int cache_pos = 0;
  static grub_hfs_datarecord_t cache_dr;

  grub_memcpy (dr, dat, sizeof (dr));

  key.forktype = 0;
  key.fileid = grub_cpu_to_be32 (file);

  if (cache && cache_file == file  && block > cache_pos)
    {
      pos = cache_pos;
      key.first_block = grub_cpu_to_be16 (pos);
      grub_memcpy (dr, cache_dr, sizeof (cache_dr));
    }

  for (;;)
    {
      int i;

      /* Try all 3 extents.  */
      for (i = 0; i < 3; i++)
	{
	  /* Check if the block is stored in this extent.  */
	  if (grub_be_to_cpu16 (dr[i].count) + pos > block)
	    {
	      int first = grub_be_to_cpu16 (dr[i].first_block);

	      /* If the cache is enabled, store the current position
		 in the tree.  */
	      if (tree && cache)
		{
		  cache_file = file;
		  cache_pos = pos;
		  grub_memcpy (cache_dr, dr, sizeof (cache_dr));
		}

	      return (grub_be_to_cpu16 (data->sblock.first_block)
		      + (first + block - pos) * GRUB_HFS_BLKS);
	    }

	  /* Try the next extent.  */
	  pos += grub_be_to_cpu16 (dr[i].count);
	}

      /* Lookup the block in the extent overflow file.  */
      key.first_block = grub_cpu_to_be16 (pos);
      tree = 1;
      grub_hfs_find_node (data, (char *) &key, data->ext_root,
			  1, (char *) &dr, sizeof (dr));
      if (grub_errno)
	return 0;
    }
}