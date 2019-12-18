#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char UINT ;
typedef  char TCHAR ;

/* Variables and functions */
 int CurrVol ; 
 scalar_t__ FF_USE_LFN ; 
 int FF_VOLUMES ; 
 scalar_t__ IsDigit (char const) ; 
 scalar_t__ IsLower (char) ; 
 char** VolumeStr ; 

__attribute__((used)) static int get_ldnumber (	/* Returns logical drive number (-1:invalid drive number or null pointer) */
	const TCHAR** path		/* Pointer to pointer to the path name */
)
{
	const TCHAR *tp, *tt;
	TCHAR tc;
	int i, vol = -1;
#if FF_STR_VOLUME_ID		/* Find string volume ID */
	const char *sp;
	char c;
#endif

	tt = tp = *path;
	if (!tp) return vol;	/* Invalid path name? */
	do tc = *tt++; while ((UINT)tc >= (FF_USE_LFN ? ' ' : '!') && tc != ':');	/* Find a colon in the path */

	if (tc == ':') {	/* DOS/Windows style volume ID? */
		i = FF_VOLUMES;
		if (IsDigit(*tp) && tp + 2 == tt) {	/* Is there a numeric volume ID + colon? */
			i = (int)*tp - '0';	/* Get the LD number */
		}
#if FF_STR_VOLUME_ID == 1	/* Arbitrary string is enabled */
		else {
			i = 0;
			do {
				sp = VolumeStr[i]; tp = *path;	/* This string volume ID and path name */
				do {	/* Compare the volume ID with path name */
					c = *sp++; tc = *tp++;
					if (IsLower(c)) c -= 0x20;
					if (IsLower(tc)) tc -= 0x20;
				} while (c && (TCHAR)c == tc);
			} while ((c || tp != tt) && ++i < FF_VOLUMES);	/* Repeat for each id until pattern match */
		}
#endif
		if (i < FF_VOLUMES) {	/* If a volume ID is found, get the drive number and strip it */
			vol = i;		/* Drive number */
			*path = tt;		/* Snip the drive prefix off */
		}
		return vol;
	}
#if FF_STR_VOLUME_ID == 2		/* Unix style volume ID is enabled */
	if (*tp == '/') {
		i = 0;
		do {
			sp = VolumeStr[i]; tp = *path;	/* This string volume ID and path name */
			do {	/* Compare the volume ID with path name */
				c = *sp++; tc = *(++tp);
				if (IsLower(c)) c -= 0x20;
				if (IsLower(tc)) tc -= 0x20;
			} while (c && (TCHAR)c == tc);
		} while ((c || (tc != '/' && (UINT)tc >= (FF_USE_LFN ? ' ' : '!'))) && ++i < FF_VOLUMES);	/* Repeat for each ID until pattern match */
		if (i < FF_VOLUMES) {	/* If a volume ID is found, get the drive number and strip it */
			vol = i;		/* Drive number */
			*path = tp;		/* Snip the drive prefix off */
			return vol;
		}
	}
#endif
	/* No drive prefix is found */
#if FF_FS_RPATH != 0
	vol = CurrVol;	/* Default drive is current drive */
#else
	vol = 0;		/* Default drive is 0 */
#endif
	return vol;		/* Return the default drive */
}