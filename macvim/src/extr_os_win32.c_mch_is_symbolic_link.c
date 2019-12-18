#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {scalar_t__ dwFileAttributes; scalar_t__ dwReserved0; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
struct TYPE_6__ {scalar_t__ dwFileAttributes; scalar_t__ dwReserved0; } ;
typedef  TYPE_2__ WIN32_FIND_DATAA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int FALSE ; 
 scalar_t__ FILE_ATTRIBUTE_REPARSE_POINT ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ GetACP () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IO_REPARSE_TAG_SYMLINK ; 
 int TRUE ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

int
mch_is_symbolic_link(char_u *fname)
{
    HANDLE		hFind;
    int			res = FALSE;
    WIN32_FIND_DATAA	findDataA;
    DWORD		fileFlags = 0, reparseTag = 0;
#ifdef FEAT_MBYTE
    WCHAR		*wn = NULL;
    WIN32_FIND_DATAW	findDataW;

    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
	wn = enc_to_utf16(fname, NULL);
    if (wn != NULL)
    {
	hFind = FindFirstFileW(wn, &findDataW);
	vim_free(wn);
	if (hFind == INVALID_HANDLE_VALUE
		&& GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
	{
	    /* Retry with non-wide function (for Windows 98). */
	    hFind = FindFirstFile(fname, &findDataA);
	    if (hFind != INVALID_HANDLE_VALUE)
	    {
		fileFlags = findDataA.dwFileAttributes;
		reparseTag = findDataA.dwReserved0;
	    }
	}
	else
	{
	    fileFlags = findDataW.dwFileAttributes;
	    reparseTag = findDataW.dwReserved0;
	}
    }
    else
#endif
    {
	hFind = FindFirstFile(fname, &findDataA);
	if (hFind != INVALID_HANDLE_VALUE)
	{
	    fileFlags = findDataA.dwFileAttributes;
	    reparseTag = findDataA.dwReserved0;
	}
    }

    if (hFind != INVALID_HANDLE_VALUE)
	FindClose(hFind);

    if ((fileFlags & FILE_ATTRIBUTE_REPARSE_POINT)
	    && reparseTag == IO_REPARSE_TAG_SYMLINK)
	res = TRUE;

    return res;
}