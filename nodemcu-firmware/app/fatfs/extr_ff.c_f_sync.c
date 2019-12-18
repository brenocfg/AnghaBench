#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fs ;
struct TYPE_14__ {int stat; scalar_t__ objsize; int /*<<< orphan*/  sclust; int /*<<< orphan*/  fs; } ;
struct TYPE_13__ {scalar_t__ fs_type; int* dirbuf; int wflag; int /*<<< orphan*/  pdrv; } ;
struct TYPE_12__ {int flag; int* dir_ptr; TYPE_3__ obj; int /*<<< orphan*/  dir_sect; int /*<<< orphan*/  clust; int /*<<< orphan*/  sect; int /*<<< orphan*/  buf; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  TYPE_2__ FATFS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DIR ;
typedef  int /*<<< orphan*/  DEF_NAMBUF ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_ARC ; 
 size_t DIR_Attr ; 
 int DIR_FileSize ; 
 int DIR_LstAccDate ; 
 int DIR_ModTime ; 
 int FA_DIRTY ; 
 int FA_MODIFIED ; 
 int /*<<< orphan*/  FREE_NAMBUF () ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 int /*<<< orphan*/  GET_FATTIME () ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 scalar_t__ RES_OK ; 
 int XDIR_AccTime ; 
 size_t XDIR_Attr ; 
 int XDIR_FileSize ; 
 int XDIR_FstClus ; 
 size_t XDIR_GenFlags ; 
 int XDIR_ModTime ; 
 size_t XDIR_ModTime10 ; 
 int XDIR_ValidFileSize ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fill_first_frag (TYPE_3__*) ; 
 scalar_t__ fill_last_frag (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ load_obj_xdir (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_clust (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_dword (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_qword (int*,scalar_t__) ; 
 int /*<<< orphan*/  st_word (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ store_xdir (int /*<<< orphan*/ *) ; 
 scalar_t__ sync_fs (TYPE_2__*) ; 
 scalar_t__ validate (TYPE_3__*,TYPE_2__**) ; 

FRESULT f_sync (
	FIL* fp		/* Pointer to the file object */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD tm;
	BYTE *dir;


	res = validate(&fp->obj, &fs);	/* Check validity of the file object */
	if (res == FR_OK) {
		if (fp->flag & FA_MODIFIED) {	/* Is there any change to the file? */
#if !FF_FS_TINY
			if (fp->flag & FA_DIRTY) {	/* Write-back cached data if needed */
				if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) LEAVE_FF(fs, FR_DISK_ERR);
				fp->flag &= (BYTE)~FA_DIRTY;
			}
#endif
			/* Update the directory entry */
			tm = GET_FATTIME();				/* Modified time */
#if FF_FS_EXFAT
			if (fs->fs_type == FS_EXFAT) {
				res = fill_first_frag(&fp->obj);	/* Fill first fragment on the FAT if needed */
				if (res == FR_OK) {
					res = fill_last_frag(&fp->obj, fp->clust, 0xFFFFFFFF);	/* Fill last fragment on the FAT if needed */
				}
				if (res == FR_OK) {
					DIR dj;
					DEF_NAMBUF

					INIT_NAMBUF(fs);
					res = load_obj_xdir(&dj, &fp->obj);	/* Load directory entry block */
					if (res == FR_OK) {
						fs->dirbuf[XDIR_Attr] |= AM_ARC;				/* Set archive attribute to indicate that the file has been changed */
						fs->dirbuf[XDIR_GenFlags] = fp->obj.stat | 1;	/* Update file allocation information */
						st_dword(fs->dirbuf + XDIR_FstClus, fp->obj.sclust);
						st_qword(fs->dirbuf + XDIR_FileSize, fp->obj.objsize);
						st_qword(fs->dirbuf + XDIR_ValidFileSize, fp->obj.objsize);
						st_dword(fs->dirbuf + XDIR_ModTime, tm);		/* Update modified time */
						fs->dirbuf[XDIR_ModTime10] = 0;
						st_dword(fs->dirbuf + XDIR_AccTime, 0);
						res = store_xdir(&dj);	/* Restore it to the directory */
						if (res == FR_OK) {
							res = sync_fs(fs);
							fp->flag &= (BYTE)~FA_MODIFIED;
						}
					}
					FREE_NAMBUF();
				}
			} else
#endif
			{
				res = move_window(fs, fp->dir_sect);
				if (res == FR_OK) {
					dir = fp->dir_ptr;
					dir[DIR_Attr] |= AM_ARC;						/* Set archive attribute to indicate that the file has been changed */
					st_clust(fp->obj.fs, dir, fp->obj.sclust);		/* Update file allocation information  */
					st_dword(dir + DIR_FileSize, (DWORD)fp->obj.objsize);	/* Update file size */
					st_dword(dir + DIR_ModTime, tm);				/* Update modified time */
					st_word(dir + DIR_LstAccDate, 0);
					fs->wflag = 1;
					res = sync_fs(fs);					/* Restore it to the directory */
					fp->flag &= (BYTE)~FA_MODIFIED;
				}
			}
		}
	}

	LEAVE_FF(fs, res);
}