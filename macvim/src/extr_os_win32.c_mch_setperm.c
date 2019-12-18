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

/* Variables and functions */
 int FAIL ; 
 scalar_t__ GetACP () ; 
 int OK ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 long _chmod (int /*<<< orphan*/ *,long) ; 
 long _wchmod (int /*<<< orphan*/ *,long) ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_PlatformId ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win32_set_archive (int /*<<< orphan*/ *) ; 

int
mch_setperm(char_u *name, long perm)
{
    long	n = -1;

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR *p = enc_to_utf16(name, NULL);

	if (p != NULL)
	{
	    n = _wchmod(p, perm);
	    vim_free(p);
	    if (n == -1 && g_PlatformId == VER_PLATFORM_WIN32_NT)
		return FAIL;
	    /* Retry with non-wide function (for Windows 98). */
	}
    }
    if (n == -1)
#endif
	n = _chmod(name, perm);
    if (n == -1)
	return FAIL;

    win32_set_archive(name);

    return OK;
}