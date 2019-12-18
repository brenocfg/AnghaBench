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
typedef  int /*<<< orphan*/  szName ;
typedef  char char_u ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int FALSE ; 
 int TRUE ; 
 int _MAX_PATH ; 
 scalar_t__ mch_FullName (char*,char*,int,int) ; 
 scalar_t__ pathcmp (char*,char*,int) ; 

int
mch_isFullName(char_u *fname)
{
#ifdef FEAT_MBYTE
    /* WinNT and later can use _MAX_PATH wide characters for a pathname, which
     * means that the maximum pathname is _MAX_PATH * 3 bytes when 'enc' is
     * UTF-8. */
    char szName[_MAX_PATH * 3 + 1];
#else
    char szName[_MAX_PATH + 1];
#endif

    /* A name like "d:/foo" and "//server/share" is absolute */
    if ((fname[0] && fname[1] == ':' && (fname[2] == '/' || fname[2] == '\\'))
	    || (fname[0] == fname[1] && (fname[0] == '/' || fname[0] == '\\')))
	return TRUE;

    /* A name that can't be made absolute probably isn't absolute. */
    if (mch_FullName(fname, szName, sizeof(szName) - 1, FALSE) == FAIL)
	return FALSE;

    return pathcmp(fname, szName, -1) == 0;
}