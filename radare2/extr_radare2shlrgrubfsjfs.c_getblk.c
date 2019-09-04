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
typedef  int /*<<< orphan*/  tree ;
struct grub_jfs_treehead {int flags; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int length2; int /*<<< orphan*/  blk2; int /*<<< orphan*/  length; } ;
struct grub_jfs_tree_extent {TYPE_1__ extent; int /*<<< orphan*/  offset2; } ;
struct getblk_closure {scalar_t__ blk; TYPE_3__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  log2_blksz; } ;
struct TYPE_6__ {TYPE_2__ sblock; int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_DISK_SECTOR_BITS ; 
 int GRUB_JFS_TREE_LEAF ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getblk (struct grub_jfs_treehead *treehead,
	struct grub_jfs_tree_extent *extents,
	struct getblk_closure *c)
{
  int found = -1;
  int i;

  for (i = 0; i < grub_le_to_cpu16 (treehead->count) - 2; i++)
    {
      if (treehead->flags & GRUB_JFS_TREE_LEAF)
	{
	  /* Read the leafnode.  */
	  if (grub_le_to_cpu32 (extents[i].offset2) <= c->blk
	      && ((grub_le_to_cpu16 (extents[i].extent.length))
		  + (extents[i].extent.length2 << 8)
		  + grub_le_to_cpu32 (extents[i].offset2)) > c->blk)
	    return (c->blk - grub_le_to_cpu32 (extents[i].offset2)
		    + grub_le_to_cpu32 (extents[i].extent.blk2));
	}
      else
	if (c->blk >= grub_le_to_cpu32 (extents[i].offset2))
	  found = i;
    }

  if (found != -1)
    {
      struct
      {
	struct grub_jfs_treehead treehead;
	struct grub_jfs_tree_extent extents[254];
      } tree;

      if (grub_disk_read (c->data->disk,
			  grub_le_to_cpu32 (extents[found].extent.blk2)
			  << (grub_le_to_cpu16 (c->data->sblock.log2_blksz)
			      - GRUB_DISK_SECTOR_BITS), 0,
			  sizeof (tree), (char *) &tree))
	return -1;

      return getblk (&tree.treehead, &tree.extents[0], c);
    }

  return -1;
}