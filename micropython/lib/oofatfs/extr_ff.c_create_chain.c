#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int last_clst; int n_fatent; scalar_t__ free_clst; scalar_t__ fs_type; int fsi_flag; } ;
struct TYPE_9__ {int stat; int n_frag; scalar_t__ sclust; scalar_t__ n_cont; TYPE_2__* fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FFOBJID ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ change_bitmap (TYPE_2__*,int,int,int) ; 
 scalar_t__ fill_last_frag (TYPE_1__*,int,int) ; 
 int find_bitmap (TYPE_2__*,int,int) ; 
 int get_fat (TYPE_1__*,int) ; 
 scalar_t__ put_fat (TYPE_2__*,int,int) ; 

__attribute__((used)) static DWORD create_chain ( /* 0:No free cluster, 1:Internal error, 0xFFFFFFFF:Disk error, >=2:New cluster# */
    FFOBJID* obj,       /* Corresponding object */
    DWORD clst          /* Cluster# to stretch, 0:Create a new chain */
)
{
    DWORD cs, ncl, scl;
    FRESULT res;
    FATFS *fs = obj->fs;


    if (clst == 0) {    /* Create a new chain */
        scl = fs->last_clst;                /* Suggested cluster to start to find */
        if (scl == 0 || scl >= fs->n_fatent) scl = 1;
    }
    else {              /* Stretch a chain */
        cs = get_fat(obj, clst);            /* Check the cluster status */
        if (cs < 2) return 1;               /* Test for insanity */
        if (cs == 0xFFFFFFFF) return cs;    /* Test for disk error */
        if (cs < fs->n_fatent) return cs;   /* It is already followed by next cluster */
        scl = clst;                         /* Cluster to start to find */
    }
    if (fs->free_clst == 0) return 0;       /* No free cluster */

#if FF_FS_EXFAT
    if (fs->fs_type == FS_EXFAT) {  /* On the exFAT volume */
        ncl = find_bitmap(fs, scl, 1);              /* Find a free cluster */
        if (ncl == 0 || ncl == 0xFFFFFFFF) return ncl;  /* No free cluster or hard error? */
        res = change_bitmap(fs, ncl, 1, 1);         /* Mark the cluster 'in use' */
        if (res == FR_INT_ERR) return 1;
        if (res == FR_DISK_ERR) return 0xFFFFFFFF;
        if (clst == 0) {                            /* Is it a new chain? */
            obj->stat = 2;                          /* Set status 'contiguous' */
        } else {                                    /* It is a stretched chain */
            if (obj->stat == 2 && ncl != scl + 1) { /* Is the chain got fragmented? */
                obj->n_cont = scl - obj->sclust;    /* Set size of the contiguous part */
                obj->stat = 3;                      /* Change status 'just fragmented' */
            }
        }
        if (obj->stat != 2) {   /* Is the file non-contiguous? */
            if (ncl == clst + 1) {  /* Is the cluster next to previous one? */
                obj->n_frag = obj->n_frag ? obj->n_frag + 1 : 2;    /* Increment size of last framgent */
            } else {                /* New fragment */
                if (obj->n_frag == 0) obj->n_frag = 1;
                res = fill_last_frag(obj, clst, ncl);   /* Fill last fragment on the FAT and link it to new one */
                if (res == FR_OK) obj->n_frag = 1;
            }
        }
    } else
#endif
    {   /* On the FAT/FAT32 volume */
        ncl = 0;
        if (scl == clst) {                      /* Stretching an existing chain? */
            ncl = scl + 1;                      /* Test if next cluster is free */
            if (ncl >= fs->n_fatent) ncl = 2;
            cs = get_fat(obj, ncl);             /* Get next cluster status */
            if (cs == 1 || cs == 0xFFFFFFFF) return cs; /* Test for error */
            if (cs != 0) {                      /* Not free? */
                cs = fs->last_clst;             /* Start at suggested cluster if it is valid */
                if (cs >= 2 && cs < fs->n_fatent) scl = cs;
                ncl = 0;
            }
        }
        if (ncl == 0) { /* The new cluster cannot be contiguous and find another fragment */
            ncl = scl;  /* Start cluster */
            for (;;) {
                ncl++;                          /* Next cluster */
                if (ncl >= fs->n_fatent) {      /* Check wrap-around */
                    ncl = 2;
                    if (ncl > scl) return 0;    /* No free cluster found? */
                }
                cs = get_fat(obj, ncl);         /* Get the cluster status */
                if (cs == 0) break;             /* Found a free cluster? */
                if (cs == 1 || cs == 0xFFFFFFFF) return cs; /* Test for error */
                if (ncl == scl) return 0;       /* No free cluster found? */
            }
        }
        res = put_fat(fs, ncl, 0xFFFFFFFF);     /* Mark the new cluster 'EOC' */
        if (res == FR_OK && clst != 0) {
            res = put_fat(fs, clst, ncl);       /* Link it from the previous one if needed */
        }
    }

    if (res == FR_OK) {         /* Update FSINFO if function succeeded. */
        fs->last_clst = ncl;
        if (fs->free_clst <= fs->n_fatent - 2) fs->free_clst--;
        fs->fsi_flag |= 1;
    } else {
        ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;    /* Failed. Generate error status */
    }

    return ncl;     /* Return new cluster number or error status */
}