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

/* Variables and functions */
 scalar_t__ DeleteFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  win32_setattrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mch_remove(char_u *name)
{
#ifdef FEAT_MBYTE
    WCHAR	*wn = NULL;
    int		n;
#endif

    win32_setattrs(name, FILE_ATTRIBUTE_NORMAL);

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	wn = enc_to_utf16(name, NULL);
	if (wn != NULL)
	{
	    n = DeleteFileW(wn) ? 0 : -1;
	    vim_free(wn);
	    if (n == 0 || GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
		return n;
	    /* Retry with non-wide function (for Windows 98). */
	}
    }
#endif
    return DeleteFile(name) ? 0 : -1;
}