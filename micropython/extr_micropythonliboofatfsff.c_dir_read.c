#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char attr; int /*<<< orphan*/ * fs; } ;
struct TYPE_6__ {char* dir; int /*<<< orphan*/  sect; TYPE_1__ obj; } ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  FATFS ;
typedef  TYPE_2__ DIR ;
typedef  char BYTE ;

/* Variables and functions */
 char AM_ARC ; 
 char AM_LFN ; 
 char AM_MASK ; 
 char AM_VOL ; 
 char DDEM ; 
 size_t DIR_Attr ; 
 size_t DIR_Name ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ dir_next (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FRESULT dir_read (
    DIR* dp,        /* Pointer to the directory object */
    int vol         /* Filtered by 0:file/directory or 1:volume label */
)
{
    FRESULT res = FR_NO_FILE;
    FATFS *fs = dp->obj.fs;
    BYTE attr, b;
#if FF_USE_LFN
    BYTE ord = 0xFF, sum = 0xFF;
#endif

    while (dp->sect) {
        res = move_window(fs, dp->sect);
        if (res != FR_OK) break;
        b = dp->dir[DIR_Name];  /* Test for the entry type */
        if (b == 0) {
            res = FR_NO_FILE; break; /* Reached to end of the directory */
        }
#if FF_FS_EXFAT
        if (fs->fs_type == FS_EXFAT) {  /* On the exFAT volume */
            if (FF_USE_LABEL && vol) {
                if (b == ET_VLABEL) break;  /* Volume label entry? */
            } else {
                if (b == ET_FILEDIR) {      /* Start of the file entry block? */
                    dp->blk_ofs = dp->dptr; /* Get location of the block */
                    res = load_xdir(dp);    /* Load the entry block */
                    if (res == FR_OK) {
                        dp->obj.attr = fs->dirbuf[XDIR_Attr] & AM_MASK; /* Get attribute */
                    }
                    break;
                }
            }
        } else
#endif
        {   /* On the FAT/FAT32 volume */
            dp->obj.attr = attr = dp->dir[DIR_Attr] & AM_MASK;  /* Get attribute */
#if FF_USE_LFN      /* LFN configuration */
            if (b == DDEM || b == '.' || (int)((attr & ~AM_ARC) == AM_VOL) != vol) {    /* An entry without valid data */
                ord = 0xFF;
            } else {
                if (attr == AM_LFN) {           /* An LFN entry is found */
                    if (b & LLEF) {         /* Is it start of an LFN sequence? */
                        sum = dp->dir[LDIR_Chksum];
                        b &= (BYTE)~LLEF; ord = b;
                        dp->blk_ofs = dp->dptr;
                    }
                    /* Check LFN validity and capture it */
                    ord = (b == ord && sum == dp->dir[LDIR_Chksum] && pick_lfn(fs->lfnbuf, dp->dir)) ? ord - 1 : 0xFF;
                } else {                    /* An SFN entry is found */
                    if (ord != 0 || sum != sum_sfn(dp->dir)) {  /* Is there a valid LFN? */
                        dp->blk_ofs = 0xFFFFFFFF;           /* It has no LFN. */
                    }
                    break;
                }
            }
#else       /* Non LFN configuration */
            if (b != DDEM && b != '.' && attr != AM_LFN && (int)((attr & ~AM_ARC) == AM_VOL) == vol) {  /* Is it a valid entry? */
                break;
            }
#endif
        }
        res = dir_next(dp, 0);      /* Next entry */
        if (res != FR_OK) break;
    }

    if (res != FR_OK) dp->sect = 0;     /* Terminate the read operation on error or EOT */
    return res;
}