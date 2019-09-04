#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* fs; } ;
struct TYPE_9__ {int /*<<< orphan*/  fn; scalar_t__ dir; int /*<<< orphan*/  sect; TYPE_1__ obj; } ;
struct TYPE_8__ {int wflag; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FATFS ;
typedef  TYPE_3__ DIR ;

/* Variables and functions */
 scalar_t__ DIR_Name ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  SZDIRE ; 
 scalar_t__ dir_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mem_cpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mem_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FRESULT dir_register (   /* FR_OK:succeeded, FR_DENIED:no free entry or too many SFN collision, FR_DISK_ERR:disk error */
    DIR* dp                     /* Target directory with object name to be created */
)
{
    FRESULT res;
    FATFS *fs = dp->obj.fs;
#if FF_USE_LFN      /* LFN configuration */
    UINT n, nlen, nent;
    BYTE sn[12], sum;


    if (dp->fn[NSFLAG] & (NS_DOT | NS_NONAME)) return FR_INVALID_NAME;  /* Check name validity */
    for (nlen = 0; fs->lfnbuf[nlen]; nlen++) ;  /* Get lfn length */

#if FF_FS_EXFAT
    if (fs->fs_type == FS_EXFAT) {  /* On the exFAT volume */
        nent = (nlen + 14) / 15 + 2;    /* Number of entries to allocate (85+C0+C1s) */
        res = dir_alloc(dp, nent);      /* Allocate directory entries */
        if (res != FR_OK) return res;
        dp->blk_ofs = dp->dptr - SZDIRE * (nent - 1);   /* Set the allocated entry block offset */

        if (dp->obj.stat & 4) {         /* Has the directory been stretched by new allocation? */
            dp->obj.stat &= ~4;
            res = fill_first_frag(&dp->obj);    /* Fill the first fragment on the FAT if needed */
            if (res != FR_OK) return res;
            res = fill_last_frag(&dp->obj, dp->clust, 0xFFFFFFFF);  /* Fill the last fragment on the FAT if needed */
            if (res != FR_OK) return res;
            if (dp->obj.sclust != 0) {      /* Is it a sub-directory? */
                DIR dj;

                res = load_obj_xdir(&dj, &dp->obj); /* Load the object status */
                if (res != FR_OK) return res;
                dp->obj.objsize += (DWORD)fs->csize * SS(fs);           /* Increase the directory size by cluster size */
                st_qword(fs->dirbuf + XDIR_FileSize, dp->obj.objsize);  /* Update the allocation status */
                st_qword(fs->dirbuf + XDIR_ValidFileSize, dp->obj.objsize);
                fs->dirbuf[XDIR_GenFlags] = dp->obj.stat | 1;
                res = store_xdir(&dj);              /* Store the object status */
                if (res != FR_OK) return res;
            }
        }

        create_xdir(fs->dirbuf, fs->lfnbuf);    /* Create on-memory directory block to be written later */
        return FR_OK;
    }
#endif
    /* On the FAT/FAT32 volume */
    mem_cpy(sn, dp->fn, 12);
    if (sn[NSFLAG] & NS_LOSS) {         /* When LFN is out of 8.3 format, generate a numbered name */
        dp->fn[NSFLAG] = NS_NOLFN;      /* Find only SFN */
        for (n = 1; n < 100; n++) {
            gen_numname(dp->fn, sn, fs->lfnbuf, n); /* Generate a numbered name */
            res = dir_find(dp);             /* Check if the name collides with existing SFN */
            if (res != FR_OK) break;
        }
        if (n == 100) return FR_DENIED;     /* Abort if too many collisions */
        if (res != FR_NO_FILE) return res;  /* Abort if the result is other than 'not collided' */
        dp->fn[NSFLAG] = sn[NSFLAG];
    }

    /* Create an SFN with/without LFNs. */
    nent = (sn[NSFLAG] & NS_LFN) ? (nlen + 12) / 13 + 1 : 1;    /* Number of entries to allocate */
    res = dir_alloc(dp, nent);      /* Allocate entries */
    if (res == FR_OK && --nent) {   /* Set LFN entry if needed */
        res = dir_sdi(dp, dp->dptr - nent * SZDIRE);
        if (res == FR_OK) {
            sum = sum_sfn(dp->fn);  /* Checksum value of the SFN tied to the LFN */
            do {                    /* Store LFN entries in bottom first */
                res = move_window(fs, dp->sect);
                if (res != FR_OK) break;
                put_lfn(fs->lfnbuf, dp->dir, (BYTE)nent, sum);
                fs->wflag = 1;
                res = dir_next(dp, 0);  /* Next entry */
            } while (res == FR_OK && --nent);
        }
    }

#else   /* Non LFN configuration */
    res = dir_alloc(dp, 1);     /* Allocate an entry for SFN */

#endif

    /* Set SFN entry */
    if (res == FR_OK) {
        res = move_window(fs, dp->sect);
        if (res == FR_OK) {
            mem_set(dp->dir, 0, SZDIRE);    /* Clean the entry */
            mem_cpy(dp->dir + DIR_Name, dp->fn, 11);    /* Put SFN */
#if FF_USE_LFN
            dp->dir[DIR_NTres] = dp->fn[NSFLAG] & (NS_BODY | NS_EXT);   /* Put NT flag */
#endif
            fs->wflag = 1;
        }
    }

    return res;
}