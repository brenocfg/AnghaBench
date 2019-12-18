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
 scalar_t__ GetACP () ; 
 char NUL ; 
 char TOLOWER_ASC (char) ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 scalar_t__ _chdrive (char) ; 
 int _wchdir (int /*<<< orphan*/ *) ; 
 int chdir (char*) ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ g_PlatformId ; 
 scalar_t__ isalpha (char) ; 
 int p_verbose ; 
 int /*<<< orphan*/  smsg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  verbose_enter () ; 
 int /*<<< orphan*/  verbose_leave () ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

int
mch_chdir(char *path)
{
    if (path[0] == NUL)		/* just checking... */
	return -1;

    if (p_verbose >= 5)
    {
	verbose_enter();
	smsg((char_u *)"chdir(%s)", path);
	verbose_leave();
    }
    if (isalpha(path[0]) && path[1] == ':')	/* has a drive name */
    {
	/* If we can change to the drive, skip that part of the path.  If we
	 * can't then the current directory may be invalid, try using chdir()
	 * with the whole path. */
	if (_chdrive(TOLOWER_ASC(path[0]) - 'a' + 1) == 0)
	    path += 2;
    }

    if (*path == NUL)		/* drive name only */
	return 0;

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR	*p = enc_to_utf16(path, NULL);
	int	n;

	if (p != NULL)
	{
	    n = _wchdir(p);
	    vim_free(p);
	    if (n == 0 || g_PlatformId == VER_PLATFORM_WIN32_NT)
		return n;
	    /* Retry with non-wide function (for Windows 98). */
	}
    }
#endif

    return chdir(path);	       /* let the normal chdir() do the rest */
}