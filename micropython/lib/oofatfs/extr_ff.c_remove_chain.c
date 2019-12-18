#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int n_fatent; scalar_t__ fs_type; int free_clst; int fsi_flag; int csize; int /*<<< orphan*/  drv; } ;
struct TYPE_8__ {int stat; int sclust; int n_cont; TYPE_2__* fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FFOBJID ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_TRIM ; 
 int /*<<< orphan*/  FF_FS_EXFAT ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ change_bitmap (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int clst2sect (TYPE_2__*,int) ; 
 int /*<<< orphan*/  disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int get_fat (TYPE_1__*,int) ; 
 scalar_t__ put_fat (TYPE_2__*,int,int) ; 

__attribute__((used)) static FRESULT remove_chain (   /* FR_OK(0):succeeded, !=0:error */
    FFOBJID* obj,       /* Corresponding object */
    DWORD clst,         /* Cluster to remove a chain from */
    DWORD pclst         /* Previous cluster of clst (0 if entire chain) */
)
{
    FRESULT res = FR_OK;
    DWORD nxt;
    FATFS *fs = obj->fs;
#if FF_FS_EXFAT || FF_USE_TRIM
    DWORD scl = clst, ecl = clst;
#endif
#if FF_USE_TRIM
    DWORD rt[2];
#endif

    if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;    /* Check if in valid range */

    /* Mark the previous cluster 'EOC' on the FAT if it exists */
    if (pclst != 0 && (!FF_FS_EXFAT || fs->fs_type != FS_EXFAT || obj->stat != 2)) {
        res = put_fat(fs, pclst, 0xFFFFFFFF);
        if (res != FR_OK) return res;
    }

    /* Remove the chain */
    do {
        nxt = get_fat(obj, clst);           /* Get cluster status */
        if (nxt == 0) break;                /* Empty cluster? */
        if (nxt == 1) return FR_INT_ERR;    /* Internal error? */
        if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;  /* Disk error? */
        if (!FF_FS_EXFAT || fs->fs_type != FS_EXFAT) {
            res = put_fat(fs, clst, 0);     /* Mark the cluster 'free' on the FAT */
            if (res != FR_OK) return res;
        }
        if (fs->free_clst < fs->n_fatent - 2) { /* Update FSINFO */
            fs->free_clst++;
            fs->fsi_flag |= 1;
        }
#if FF_FS_EXFAT || FF_USE_TRIM
        if (ecl + 1 == nxt) {   /* Is next cluster contiguous? */
            ecl = nxt;
        } else {                /* End of contiguous cluster block */
#if FF_FS_EXFAT
            if (fs->fs_type == FS_EXFAT) {
                res = change_bitmap(fs, scl, ecl - scl + 1, 0); /* Mark the cluster block 'free' on the bitmap */
                if (res != FR_OK) return res;
            }
#endif
#if FF_USE_TRIM
            rt[0] = clst2sect(fs, scl);                 /* Start of data area freed */
            rt[1] = clst2sect(fs, ecl) + fs->csize - 1; /* End of data area freed */
            disk_ioctl(fs->drv, CTRL_TRIM, rt);         /* Inform device the data in the block is no longer needed */
#endif
            scl = ecl = nxt;
        }
#endif
        clst = nxt;                 /* Next cluster */
    } while (clst < fs->n_fatent);  /* Repeat while not the last link */

#if FF_FS_EXFAT
    /* Some post processes for chain status */
    if (fs->fs_type == FS_EXFAT) {
        if (pclst == 0) {   /* Has the entire chain been removed? */
            obj->stat = 0;      /* Change the chain status 'initial' */
        } else {
            if (obj->stat == 0) {   /* Is it a fragmented chain from the beginning of this session? */
                clst = obj->sclust;     /* Follow the chain to check if it gets contiguous */
                while (clst != pclst) {
                    nxt = get_fat(obj, clst);
                    if (nxt < 2) return FR_INT_ERR;
                    if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;
                    if (nxt != clst + 1) break; /* Not contiguous? */
                    clst++;
                }
                if (clst == pclst) {    /* Has the chain got contiguous again? */
                    obj->stat = 2;      /* Change the chain status 'contiguous' */
                }
            } else {
                if (obj->stat == 3 && pclst >= obj->sclust && pclst <= obj->sclust + obj->n_cont) { /* Was the chain fragmented in this session and got contiguous again? */
                    obj->stat = 2;  /* Change the chain status 'contiguous' */
                }
            }
        }
    }
#endif
    return FR_OK;
}