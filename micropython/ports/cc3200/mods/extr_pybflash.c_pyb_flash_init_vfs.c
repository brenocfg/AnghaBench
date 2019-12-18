#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* mp_obj_t ;
struct TYPE_9__ {void** ioctl; } ;
struct TYPE_10__ {int flags; TYPE_3__ u; void** writeblocks; void** readblocks; } ;
struct TYPE_8__ {TYPE_5__* drv; } ;
struct TYPE_7__ {int /*<<< orphan*/ * type; } ;
struct TYPE_11__ {TYPE_4__ blockdev; TYPE_2__ fatfs; TYPE_1__ base; } ;
typedef  TYPE_5__ fs_user_mount_t ;

/* Variables and functions */
 int MP_BLOCKDEV_FLAG_HAVE_IOCTL ; 
 int MP_BLOCKDEV_FLAG_NATIVE ; 
 int /*<<< orphan*/  mp_fat_vfs_type ; 
 int /*<<< orphan*/  pyb_flash_ioctl_obj ; 
 int /*<<< orphan*/  pyb_flash_obj ; 
 int /*<<< orphan*/  pyb_flash_readblocks_obj ; 
 int /*<<< orphan*/  pyb_flash_writeblocks_obj ; 
 scalar_t__ sflash_disk_read ; 
 scalar_t__ sflash_disk_write ; 

void pyb_flash_init_vfs(fs_user_mount_t *vfs) {
    vfs->base.type = &mp_fat_vfs_type;
    vfs->blockdev.flags |= MP_BLOCKDEV_FLAG_NATIVE | MP_BLOCKDEV_FLAG_HAVE_IOCTL;
    vfs->fatfs.drv = vfs;
    vfs->blockdev.readblocks[0] = (mp_obj_t)&pyb_flash_readblocks_obj;
    vfs->blockdev.readblocks[1] = (mp_obj_t)&pyb_flash_obj;
    vfs->blockdev.readblocks[2] = (mp_obj_t)sflash_disk_read; // native version
    vfs->blockdev.writeblocks[0] = (mp_obj_t)&pyb_flash_writeblocks_obj;
    vfs->blockdev.writeblocks[1] = (mp_obj_t)&pyb_flash_obj;
    vfs->blockdev.writeblocks[2] = (mp_obj_t)sflash_disk_write; // native version
    vfs->blockdev.u.ioctl[0] = (mp_obj_t)&pyb_flash_ioctl_obj;
    vfs->blockdev.u.ioctl[1] = (mp_obj_t)&pyb_flash_obj;
}