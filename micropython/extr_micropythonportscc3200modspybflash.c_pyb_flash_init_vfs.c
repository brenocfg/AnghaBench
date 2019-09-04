#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* mp_obj_t ;
struct TYPE_8__ {void** ioctl; } ;
struct TYPE_7__ {TYPE_4__* drv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * type; } ;
struct TYPE_9__ {int flags; TYPE_3__ u; void** writeblocks; void** readblocks; TYPE_2__ fatfs; TYPE_1__ base; } ;
typedef  TYPE_4__ fs_user_mount_t ;

/* Variables and functions */
 int FSUSER_HAVE_IOCTL ; 
 int FSUSER_NATIVE ; 
 int /*<<< orphan*/  mp_fat_vfs_type ; 
 int /*<<< orphan*/  pyb_flash_ioctl_obj ; 
 int /*<<< orphan*/  pyb_flash_obj ; 
 int /*<<< orphan*/  pyb_flash_readblocks_obj ; 
 int /*<<< orphan*/  pyb_flash_writeblocks_obj ; 
 scalar_t__ sflash_disk_read ; 
 scalar_t__ sflash_disk_write ; 

void pyb_flash_init_vfs(fs_user_mount_t *vfs) {
    vfs->base.type = &mp_fat_vfs_type;
    vfs->flags |= FSUSER_NATIVE | FSUSER_HAVE_IOCTL;
    vfs->fatfs.drv = vfs;
    vfs->readblocks[0] = (mp_obj_t)&pyb_flash_readblocks_obj;
    vfs->readblocks[1] = (mp_obj_t)&pyb_flash_obj;
    vfs->readblocks[2] = (mp_obj_t)sflash_disk_read; // native version
    vfs->writeblocks[0] = (mp_obj_t)&pyb_flash_writeblocks_obj;
    vfs->writeblocks[1] = (mp_obj_t)&pyb_flash_obj;
    vfs->writeblocks[2] = (mp_obj_t)sflash_disk_write; // native version
    vfs->u.ioctl[0] = (mp_obj_t)&pyb_flash_ioctl_obj;
    vfs->u.ioctl[1] = (mp_obj_t)&pyb_flash_obj;
}