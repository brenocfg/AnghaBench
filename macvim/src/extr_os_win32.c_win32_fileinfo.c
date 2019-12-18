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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int FILEINFO_ENC_FAIL ; 
 int FILEINFO_INFO_FAIL ; 
 int FILEINFO_OK ; 
 int FILEINFO_READ_FAIL ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetACP () ; 
 scalar_t__ GetFileInformationByHandle (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

int
win32_fileinfo(char_u *fname, BY_HANDLE_FILE_INFORMATION *info)
{
    HANDLE	hFile;
    int		res = FILEINFO_READ_FAIL;
#ifdef FEAT_MBYTE
    WCHAR	*wn = NULL;

    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	wn = enc_to_utf16(fname, NULL);
	if (wn == NULL)
	    res = FILEINFO_ENC_FAIL;
    }
    if (wn != NULL)
    {
	hFile = CreateFileW(wn,		/* file name */
		    GENERIC_READ,	/* access mode */
		    FILE_SHARE_READ | FILE_SHARE_WRITE,	/* share mode */
		    NULL,		/* security descriptor */
		    OPEN_EXISTING,	/* creation disposition */
		    FILE_FLAG_BACKUP_SEMANTICS,	/* file attributes */
		    NULL);		/* handle to template file */
	if (hFile == INVALID_HANDLE_VALUE
			      && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
	{
	    /* Retry with non-wide function (for Windows 98). */
	    vim_free(wn);
	    wn = NULL;
	}
    }
    if (wn == NULL)
#endif
	hFile = CreateFile(fname,	/* file name */
		    GENERIC_READ,	/* access mode */
		    FILE_SHARE_READ | FILE_SHARE_WRITE,	/* share mode */
		    NULL,		/* security descriptor */
		    OPEN_EXISTING,	/* creation disposition */
		    FILE_FLAG_BACKUP_SEMANTICS,	/* file attributes */
		    NULL);		/* handle to template file */

    if (hFile != INVALID_HANDLE_VALUE)
    {
	if (GetFileInformationByHandle(hFile, info) != 0)
	    res = FILEINFO_OK;
	else
	    res = FILEINFO_INFO_FAIL;
	CloseHandle(hFile);
    }

#ifdef FEAT_MBYTE
    vim_free(wn);
#endif
    return res;
}