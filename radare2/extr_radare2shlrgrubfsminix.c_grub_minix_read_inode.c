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
struct grub_minix_sblock {int /*<<< orphan*/  zone_bmap_size; int /*<<< orphan*/  inode_bmap_size; } ;
struct grub_minix_inode {int dummy; } ;
struct grub_minix_data {int ino; int version; int /*<<< orphan*/  inode2; int /*<<< orphan*/  disk; int /*<<< orphan*/  inode; struct grub_minix_sblock sblock; } ;
struct grub_minix2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int GRUB_DISK_SECTOR_SIZE ; 
 int /*<<< orphan*/  GRUB_ERR_NONE ; 
 int GRUB_MINIX_LOG2_BSIZE ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_minix_read_inode (struct grub_minix_data *data, int ino)
{
  struct grub_minix_sblock *sblock = &data->sblock;

  /* Block in which the inode is stored.  */
  int block;
  data->ino = ino;

  /* The first inode in minix is inode 1.  */
  ino--;

  block = ((2 + grub_le_to_cpu16 (sblock->inode_bmap_size)
	    + grub_le_to_cpu16 (sblock->zone_bmap_size))
	   << GRUB_MINIX_LOG2_BSIZE);

  if (data->version == 1)
    {
      block += ino / (GRUB_DISK_SECTOR_SIZE / sizeof (struct grub_minix_inode));
      int offs = (ino % (GRUB_DISK_SECTOR_SIZE
			 / sizeof (struct grub_minix_inode))
		  * sizeof (struct grub_minix_inode));

      grub_disk_read (data->disk, block, offs,
		      sizeof (struct grub_minix_inode), &data->inode);
    }
  else
    {
      block += ino / (GRUB_DISK_SECTOR_SIZE
		      / sizeof (struct grub_minix2_inode));
      int offs = (ino
		  % (GRUB_DISK_SECTOR_SIZE / sizeof (struct grub_minix2_inode))
		  * sizeof (struct grub_minix2_inode));

      grub_disk_read (data->disk, block, offs,
		      sizeof (struct grub_minix2_inode),&data->inode2);
    }

  return GRUB_ERR_NONE;
}