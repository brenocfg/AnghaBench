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
struct TYPE_9__ {int sclust; scalar_t__ stat; TYPE_1__* fs; } ;
struct TYPE_8__ {int dptr; scalar_t__ sect; int clust; scalar_t__ dir; TYPE_3__ obj; } ;
struct TYPE_7__ {scalar_t__ fs_type; int dirbase; int n_rootdir; int n_fatent; scalar_t__ win; scalar_t__ csize; } ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  TYPE_2__ DIR ;

/* Variables and functions */
 scalar_t__ FF_FS_EXFAT ; 
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_INT_ERR ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ FS_FAT32 ; 
 scalar_t__ MAX_DIR ; 
 scalar_t__ MAX_DIR_EX ; 
 int SS (TYPE_1__*) ; 
 int SZDIRE ; 
 scalar_t__ clst2sect (TYPE_1__*,int) ; 
 int get_fat (TYPE_3__*,int) ; 

__attribute__((used)) static FRESULT dir_sdi (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,		/* Pointer to directory object */
	DWORD ofs		/* Offset of directory table */
)
{
	DWORD csz, clst;
	FATFS *fs = dp->obj.fs;


	if (ofs >= (DWORD)((FF_FS_EXFAT && fs->fs_type == FS_EXFAT) ? MAX_DIR_EX : MAX_DIR) || ofs % SZDIRE) {	/* Check range of offset and alignment */
		return FR_INT_ERR;
	}
	dp->dptr = ofs;				/* Set current offset */
	clst = dp->obj.sclust;		/* Table start cluster (0:root) */
	if (clst == 0 && fs->fs_type >= FS_FAT32) {	/* Replace cluster# 0 with root cluster# */
		clst = fs->dirbase;
		if (FF_FS_EXFAT) dp->obj.stat = 0;	/* exFAT: Root dir has an FAT chain */
	}

	if (clst == 0) {	/* Static table (root-directory on the FAT volume) */
		if (ofs / SZDIRE >= fs->n_rootdir) return FR_INT_ERR;	/* Is index out of range? */
		dp->sect = fs->dirbase;

	} else {			/* Dynamic table (sub-directory or root-directory on the FAT32/exFAT volume) */
		csz = (DWORD)fs->csize * SS(fs);	/* Bytes per cluster */
		while (ofs >= csz) {				/* Follow cluster chain */
			clst = get_fat(&dp->obj, clst);				/* Get next cluster */
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
			if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;	/* Reached to end of table or internal error */
			ofs -= csz;
		}
		dp->sect = clst2sect(fs, clst);
	}
	dp->clust = clst;					/* Current cluster# */
	if (dp->sect == 0) return FR_INT_ERR;
	dp->sect += ofs / SS(fs);			/* Sector# of the directory entry */
	dp->dir = fs->win + (ofs % SS(fs));	/* Pointer to the entry in the win[] */

	return FR_OK;
}