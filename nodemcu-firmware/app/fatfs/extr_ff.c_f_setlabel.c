#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  char UINT ;
struct TYPE_10__ {scalar_t__ sclust; TYPE_2__* fs; } ;
struct TYPE_12__ {int* dir; TYPE_1__ obj; } ;
struct TYPE_11__ {scalar_t__ fs_type; int wflag; } ;
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;
typedef  TYPE_3__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_VOL ; 
 int /*<<< orphan*/  CODEPAGE ; 
 int DDEM ; 
 size_t DIR_Attr ; 
 size_t DIR_Name ; 
 scalar_t__ DIR_READ_LABEL (TYPE_3__*) ; 
 int ET_VLABEL ; 
 int* ExCvt ; 
 int /*<<< orphan*/  FA_WRITE ; 
 scalar_t__ FF_FS_EXFAT ; 
 scalar_t__ FR_INVALID_NAME ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ IsLower (int) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 int SZDIRE ; 
 int XDIR_Label ; 
 size_t XDIR_NumLabel ; 
 size_t XDIR_Type ; 
 scalar_t__ chk_chr (char const*,int) ; 
 scalar_t__ dbc_1st (int) ; 
 scalar_t__ dbc_2nd (int) ; 
 scalar_t__ dir_alloc (TYPE_3__*,int) ; 
 scalar_t__ dir_sdi (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_uni2oem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_wtoupper (int) ; 
 scalar_t__ find_volume (scalar_t__ const**,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cpy (int*,int*,int) ; 
 int /*<<< orphan*/  mem_set (int*,char,int) ; 
 int /*<<< orphan*/  st_word (int*,int) ; 
 scalar_t__ sync_fs (TYPE_2__*) ; 
 int tchar2uni (scalar_t__ const**) ; 

FRESULT f_setlabel (
	const TCHAR* label	/* Volume label to set with heading logical drive number */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	BYTE dirvn[22];
	UINT di;
	WCHAR wc;
	static const char badchr[] = "+.,;=[]/\\\"*:<>\?|\x7F";	/* [0..] for FAT, [7..] for exFAT */
#if FF_USE_LFN
	DWORD dc;
#endif

	/* Get logical drive */
	res = find_volume(&label, &fs, FA_WRITE);
	if (res != FR_OK) LEAVE_FF(fs, res);

#if FF_FS_EXFAT
	if (fs->fs_type == FS_EXFAT) {	/* On the exFAT volume */
		mem_set(dirvn, 0, 22);
		di = 0;
		while ((UINT)*label >= ' ') {	/* Create volume label */
			dc = tchar2uni(&label);	/* Get a Unicode character */
			if (dc >= 0x10000) {
				if (dc == 0xFFFFFFFF || di >= 10) {	/* Wrong surrogate or buffer overflow */
					dc = 0;
				} else {
					st_word(dirvn + di * 2, (WCHAR)(dc >> 16)); di++;
				}
			}
			if (dc == 0 || chk_chr(badchr + 7, (int)dc) || di >= 11) {	/* Check validity of the volume label */
				LEAVE_FF(fs, FR_INVALID_NAME);
			}
			st_word(dirvn + di * 2, (WCHAR)dc); di++;
		}
	} else
#endif
	{	/* On the FAT/FAT32 volume */
		mem_set(dirvn, ' ', 11);
		di = 0;
		while ((UINT)*label >= ' ') {	/* Create volume label */
#if FF_USE_LFN
			dc = tchar2uni(&label);
			wc = (dc < 0x10000) ? ff_uni2oem(ff_wtoupper(dc), CODEPAGE) : 0;
#else									/* ANSI/OEM input */
			wc = (BYTE)*label++;
			if (dbc_1st((BYTE)wc)) wc = dbc_2nd((BYTE)*label) ? wc << 8 | (BYTE)*label++ : 0;
			if (IsLower(wc)) wc -= 0x20;		/* To upper ASCII characters */
#if FF_CODE_PAGE == 0
			if (ExCvt && wc >= 0x80) wc = ExCvt[wc - 0x80];	/* To upper extended characters (SBCS cfg) */
#elif FF_CODE_PAGE < 900
			if (wc >= 0x80) wc = ExCvt[wc - 0x80];	/* To upper extended characters (SBCS cfg) */
#endif
#endif
			if (wc == 0 || chk_chr(badchr + 0, (int)wc) || di >= (UINT)((wc >= 0x100) ? 10 : 11)) {	/* Reject invalid characters for volume label */
				LEAVE_FF(fs, FR_INVALID_NAME);
			}
			if (wc >= 0x100) dirvn[di++] = (BYTE)(wc >> 8);
			dirvn[di++] = (BYTE)wc;
		}
		if (dirvn[0] == DDEM) LEAVE_FF(fs, FR_INVALID_NAME);	/* Reject illegal name (heading DDEM) */
		while (di && dirvn[di - 1] == ' ') di--;				/* Snip trailing spaces */
	}

	/* Set volume label */
	dj.obj.fs = fs; dj.obj.sclust = 0;	/* Open root directory */
	res = dir_sdi(&dj, 0);
	if (res == FR_OK) {
		res = DIR_READ_LABEL(&dj);	/* Get volume label entry */
		if (res == FR_OK) {
			if (FF_FS_EXFAT && fs->fs_type == FS_EXFAT) {
				dj.dir[XDIR_NumLabel] = (BYTE)di;	/* Change the volume label */
				mem_cpy(dj.dir + XDIR_Label, dirvn, 22);
			} else {
				if (di != 0) {
					mem_cpy(dj.dir, dirvn, 11);	/* Change the volume label */
				} else {
					dj.dir[DIR_Name] = DDEM;	/* Remove the volume label */
				}
			}
			fs->wflag = 1;
			res = sync_fs(fs);
		} else {			/* No volume label entry or an error */
			if (res == FR_NO_FILE) {
				res = FR_OK;
				if (di != 0) {	/* Create a volume label entry */
					res = dir_alloc(&dj, 1);	/* Allocate an entry */
					if (res == FR_OK) {
						mem_set(dj.dir, 0, SZDIRE);	/* Clean the entry */
						if (FF_FS_EXFAT && fs->fs_type == FS_EXFAT) {
							dj.dir[XDIR_Type] = ET_VLABEL;	/* Create volume label entry */
							dj.dir[XDIR_NumLabel] = (BYTE)di;
							mem_cpy(dj.dir + XDIR_Label, dirvn, 22);
						} else {
							dj.dir[DIR_Attr] = AM_VOL;		/* Create volume label entry */
							mem_cpy(dj.dir, dirvn, 11);
						}
						fs->wflag = 1;
						res = sync_fs(fs);
					}
				}
			}
		}
	}

	LEAVE_FF(fs, res);
}