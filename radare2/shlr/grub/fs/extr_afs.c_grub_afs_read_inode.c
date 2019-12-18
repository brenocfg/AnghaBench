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
struct grub_afs_inode {int dummy; } ;
struct TYPE_2__ {int block_size; } ;
struct grub_afs_data {TYPE_1__ sblock; int /*<<< orphan*/  disk; } ;
typedef  int grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int GRUB_DISK_SECTOR_BITS ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct grub_afs_inode*) ; 

__attribute__((used)) static grub_err_t
grub_afs_read_inode (struct grub_afs_data *data,
                     grub_uint32_t ino, struct grub_afs_inode *inode)
{
  return grub_disk_read (data->disk,
                         ino *
                         (data->sblock.block_size >> GRUB_DISK_SECTOR_BITS),
                         0, sizeof (struct grub_afs_inode),
                         inode);
}