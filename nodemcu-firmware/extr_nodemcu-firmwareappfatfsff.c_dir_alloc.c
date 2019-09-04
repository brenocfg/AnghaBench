#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/ * fs; } ;
struct TYPE_7__ {scalar_t__* dir; int /*<<< orphan*/  sect; TYPE_1__ obj; } ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  FATFS ;
typedef  TYPE_2__ DIR ;

/* Variables and functions */
 scalar_t__ DDEM ; 
 size_t DIR_Name ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ dir_next (TYPE_2__*,int) ; 
 scalar_t__ dir_sdi (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FRESULT dir_alloc (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,				/* Pointer to the directory object */
	UINT nent				/* Number of contiguous entries to allocate */
)
{
	FRESULT res;
	UINT n;
	FATFS *fs = dp->obj.fs;


	res = dir_sdi(dp, 0);
	if (res == FR_OK) {
		n = 0;
		do {
			res = move_window(fs, dp->sect);
			if (res != FR_OK) break;
#if FF_FS_EXFAT
			if ((fs->fs_type == FS_EXFAT) ? (int)((dp->dir[XDIR_Type] & 0x80) == 0) : (int)(dp->dir[DIR_Name] == DDEM || dp->dir[DIR_Name] == 0)) {
#else
			if (dp->dir[DIR_Name] == DDEM || dp->dir[DIR_Name] == 0) {
#endif
				if (++n == nent) break;	/* A block of contiguous free entries is found */
			} else {
				n = 0;					/* Not a blank entry. Restart to search */
			}
			res = dir_next(dp, 1);
		} while (res == FR_OK);	/* Next entry with table stretch enabled */
	}

	if (res == FR_NO_FILE) res = FR_DENIED;	/* No directory entry to allocate */
	return res;
}