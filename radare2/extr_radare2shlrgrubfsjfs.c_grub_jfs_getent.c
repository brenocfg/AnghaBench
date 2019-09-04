#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct grub_jfs_leaf_next_dirent {int next; int /*<<< orphan*/  namepart; } ;
struct grub_jfs_leaf_dirent {int len; int next; int /*<<< orphan*/  inode; int /*<<< orphan*/  namepart; } ;
struct grub_jfs_diropen {size_t index; size_t count; scalar_t__ name; struct grub_jfs_leaf_next_dirent* next_leaf; int /*<<< orphan*/  ino; scalar_t__* sorted; struct grub_jfs_leaf_dirent* leaf; TYPE_7__* dirpage; TYPE_5__* data; TYPE_3__* inode; } ;
typedef  int /*<<< orphan*/  grub_uint8_t ;
typedef  int /*<<< orphan*/  grub_uint16_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
struct TYPE_13__ {int sindex; size_t count; int /*<<< orphan*/  nextb; } ;
struct TYPE_14__ {TYPE_6__ header; scalar_t__* sorted; struct grub_jfs_leaf_next_dirent* next_dirent; struct grub_jfs_leaf_dirent* dirent; } ;
struct TYPE_11__ {int /*<<< orphan*/  blksz; int /*<<< orphan*/  log2_blksz; } ;
struct TYPE_12__ {TYPE_4__ sblock; int /*<<< orphan*/  disk; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {TYPE_1__ tree; } ;
struct TYPE_10__ {TYPE_2__ file; } ;

/* Variables and functions */
 unsigned int GRUB_DISK_SECTOR_BITS ; 
 int /*<<< orphan*/  GRUB_ERR_OUT_OF_RANGE ; 
 int GRUB_JFS_TREE_LEAF ; 
 int /*<<< orphan*/  addstr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  grub_errno ; 
 unsigned int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 unsigned int grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 char* grub_utf16_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static grub_err_t
grub_jfs_getent (struct grub_jfs_diropen *diro)
{
  int strpos = 0;
  struct grub_jfs_leaf_dirent *leaf;
  struct grub_jfs_leaf_next_dirent *next_leaf;
  int len;
  int nextent;
  grub_uint16_t filename[255];

  /* Add the unicode string to the utf16 filename buffer.  */

  /* The last node, read in more.  */
  if (diro->index == diro->count)
    {
      unsigned int next;

      /* If the inode contains the entry tree or if this was the last
	 node, there is nothing to read.  */
      if ((diro->inode->file.tree.flags & GRUB_JFS_TREE_LEAF)
	  || !grub_le_to_cpu64 (diro->dirpage->header.nextb))
	return GRUB_ERR_OUT_OF_RANGE;

      next = grub_le_to_cpu64 (diro->dirpage->header.nextb);
      next <<= (grub_le_to_cpu16 (diro->data->sblock.log2_blksz)
		- GRUB_DISK_SECTOR_BITS);

      if (grub_disk_read (diro->data->disk, next, 0,
			  grub_le_to_cpu32 (diro->data->sblock.blksz),
			  diro->dirpage->sorted))
	return grub_errno;

      diro->leaf = diro->dirpage->dirent;
      diro->next_leaf = diro->dirpage->next_dirent;
      diro->sorted = &diro->dirpage->sorted[diro->dirpage->header.sindex * 32];
      diro->count = diro->dirpage->header.count;
      diro->index = 0;
    }

  leaf = &diro->leaf[(int) diro->sorted[diro->index]];

  len = leaf->len;
  if (!len)
    {
      diro->index++;
      return grub_jfs_getent (diro);
    }

  addstr (leaf->namepart, len < 11 ? len : 11, filename, &strpos);
  diro->ino = grub_le_to_cpu32 (leaf->inode);
  len -= 11;

  /* Move down to the leaf level.  */
  nextent = leaf->next;
  if (leaf->next != 255)
    do
      {
 	next_leaf = &diro->next_leaf[nextent];
	addstr (next_leaf->namepart, len < 15 ? len : 15, filename, &strpos);

	len -= 15;
	nextent = next_leaf->next;
      } while (next_leaf->next != 255 && len > 0);

  diro->index++;

  /* Convert the temporary UTF16 filename to UTF8.  */
  *grub_utf16_to_utf8 ((grub_uint8_t *) (diro->name), filename, strpos) = '\0';

  return 0;
}