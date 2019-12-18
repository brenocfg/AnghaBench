#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* fs; } ;
struct TYPE_10__ {scalar_t__ dptr; int blk_ofs; int* dir; int /*<<< orphan*/  sect; TYPE_1__ obj; } ;
struct TYPE_9__ {scalar_t__ fs_type; int wflag; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FATFS ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_3__ DIR ;

/* Variables and functions */
 void* DDEM ; 
 size_t DIR_Name ; 
 scalar_t__ FF_FS_EXFAT ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 size_t XDIR_Type ; 
 scalar_t__ dir_next (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_3__*,int) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FRESULT dir_remove ( /* FR_OK:Succeeded, FR_DISK_ERR:A disk error */
    DIR* dp                 /* Directory object pointing the entry to be removed */
)
{
    FRESULT res;
    FATFS *fs = dp->obj.fs;
#if FF_USE_LFN      /* LFN configuration */
    DWORD last = dp->dptr;

    res = (dp->blk_ofs == 0xFFFFFFFF) ? FR_OK : dir_sdi(dp, dp->blk_ofs);   /* Goto top of the entry block if LFN is exist */
    if (res == FR_OK) {
        do {
            res = move_window(fs, dp->sect);
            if (res != FR_OK) break;
            if (FF_FS_EXFAT && fs->fs_type == FS_EXFAT) {   /* On the exFAT volume */
                dp->dir[XDIR_Type] &= 0x7F; /* Clear the entry InUse flag. */
            } else {                                    /* On the FAT/FAT32 volume */
                dp->dir[DIR_Name] = DDEM;   /* Mark the entry 'deleted'. */
            }
            fs->wflag = 1;
            if (dp->dptr >= last) break;    /* If reached last entry then all entries of the object has been deleted. */
            res = dir_next(dp, 0);  /* Next entry */
        } while (res == FR_OK);
        if (res == FR_NO_FILE) res = FR_INT_ERR;
    }
#else           /* Non LFN configuration */

    res = move_window(fs, dp->sect);
    if (res == FR_OK) {
        dp->dir[DIR_Name] = DDEM;   /* Mark the entry 'deleted'.*/
        fs->wflag = 1;
    }
#endif

    return res;
}