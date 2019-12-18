#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
struct TYPE_9__ {scalar_t__ sclust; TYPE_2__* fs; } ;
struct TYPE_11__ {int* dir; TYPE_1__ obj; } ;
struct TYPE_10__ {int fs_type; scalar_t__ win; int /*<<< orphan*/  volbase; } ;
typedef  char TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;
typedef  TYPE_3__ DIR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int BPB_VolIDEx ; 
 int BS_VolID ; 
 int BS_VolID32 ; 
 int /*<<< orphan*/  CODEPAGE ; 
 scalar_t__ DIR_READ_LABEL (TYPE_3__*) ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
#define  FS_EXFAT 129 
#define  FS_FAT32 128 
 scalar_t__ IsSurrogate (scalar_t__) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 int XDIR_Label ; 
 size_t XDIR_NumLabel ; 
 scalar_t__ dbc_1st (int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_oem2uni (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_volume (char const**,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int ld_dword (scalar_t__) ; 
 scalar_t__ ld_word (int*) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ put_utf (scalar_t__,char*,int) ; 

FRESULT f_getlabel (
	const TCHAR* path,	/* Logical drive number */
	TCHAR* label,		/* Buffer to store the volume label */
	DWORD* vsn			/* Variable to store the volume serial number */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	UINT si, di;
	WCHAR wc;

	/* Get logical drive */
	res = find_volume(&path, &fs, 0);

	/* Get volume label */
	if (res == FR_OK && label) {
		dj.obj.fs = fs; dj.obj.sclust = 0;	/* Open root directory */
		res = dir_sdi(&dj, 0);
		if (res == FR_OK) {
		 	res = DIR_READ_LABEL(&dj);		/* Find a volume label entry */
		 	if (res == FR_OK) {
#if FF_FS_EXFAT
				if (fs->fs_type == FS_EXFAT) {
					WCHAR hs;

					for (si = di = hs = 0; si < dj.dir[XDIR_NumLabel]; si++) {	/* Extract volume label from 83 entry */
						wc = ld_word(dj.dir + XDIR_Label + si * 2);
						if (hs == 0 && IsSurrogate(wc)) {	/* Is the code a surrogate? */
							hs = wc; continue;
						}
						wc = put_utf((DWORD)hs << 16 | wc, &label[di], 4);
						if (wc == 0) { di = 0; break; }
						di += wc;
						hs = 0;
					}
					if (hs != 0) di = 0;	/* Broken surrogate pair? */
					label[di] = 0;
				} else
#endif
				{
					si = di = 0;		/* Extract volume label from AM_VOL entry */
					while (si < 11) {
						wc = dj.dir[si++];
#if FF_USE_LFN && FF_LFN_UNICODE >= 1 	/* Unicode output */
						if (dbc_1st((BYTE)wc) && si < 11) wc = wc << 8 | dj.dir[si++];	/* Is it a DBC? */
						wc = ff_oem2uni(wc, CODEPAGE);					/* Convert it into Unicode */
						if (wc != 0) wc = put_utf(wc, &label[di], 4);	/* Put it in Unicode */
						if (wc == 0) { di = 0; break; }
						di += wc;
#else									/* ANSI/OEM output */
						label[di++] = (TCHAR)wc;
#endif
					}
					do {				/* Truncate trailing spaces */
						label[di] = 0;
						if (di == 0) break;
					} while (label[--di] == ' ');
				}
			}
		}
		if (res == FR_NO_FILE) {	/* No label entry and return nul string */
			label[0] = 0;
			res = FR_OK;
		}
	}

	/* Get volume serial number */
	if (res == FR_OK && vsn) {
		res = move_window(fs, fs->volbase);
		if (res == FR_OK) {
			switch (fs->fs_type) {
			case FS_EXFAT:
				di = BPB_VolIDEx; break;

			case FS_FAT32:
				di = BS_VolID32; break;

			default:
				di = BS_VolID;
			}
			*vsn = ld_dword(fs->win + di);
		}
	}

	LEAVE_FF(fs, res);
}