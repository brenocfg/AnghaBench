#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fs_type; int fsi_flag; int free_clst; int last_clst; int /*<<< orphan*/  pdrv; scalar_t__ winsect; scalar_t__ win; scalar_t__ volbase; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;

/* Variables and functions */
 scalar_t__ BS_55AA ; 
 int /*<<< orphan*/  CTRL_SYNC ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FSI_Free_Count ; 
 scalar_t__ FSI_LeadSig ; 
 scalar_t__ FSI_Nxt_Free ; 
 scalar_t__ FSI_StrucSig ; 
 scalar_t__ FS_FAT32 ; 
 scalar_t__ RES_OK ; 
 scalar_t__ disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mem_set (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_dword (scalar_t__,int) ; 
 int /*<<< orphan*/  st_word (scalar_t__,int) ; 
 scalar_t__ sync_window (TYPE_1__*) ; 

__attribute__((used)) static FRESULT sync_fs (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS* fs		/* Filesystem object */
)
{
	FRESULT res;


	res = sync_window(fs);
	if (res == FR_OK) {
		if (fs->fs_type == FS_FAT32 && fs->fsi_flag == 1) {	/* FAT32: Update FSInfo sector if needed */
			/* Create FSInfo structure */
			mem_set(fs->win, 0, sizeof fs->win);
			st_word(fs->win + BS_55AA, 0xAA55);
			st_dword(fs->win + FSI_LeadSig, 0x41615252);
			st_dword(fs->win + FSI_StrucSig, 0x61417272);
			st_dword(fs->win + FSI_Free_Count, fs->free_clst);
			st_dword(fs->win + FSI_Nxt_Free, fs->last_clst);
			/* Write it into the FSInfo sector */
			fs->winsect = fs->volbase + 1;
			disk_write(fs->pdrv, fs->win, fs->winsect, 1);
			fs->fsi_flag = 0;
		}
		/* Make sure that no pending write process in the lower layer */
		if (disk_ioctl(fs->pdrv, CTRL_SYNC, 0) != RES_OK) res = FR_DISK_ERR;
	}

	return res;
}