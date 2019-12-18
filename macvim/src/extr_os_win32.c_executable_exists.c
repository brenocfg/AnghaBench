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
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 scalar_t__ GetACP () ; 
 int GetFileAttributesW (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ SearchPath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*,char**) ; 
 scalar_t__ SearchPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int TRUE ; 
 int _MAX_PATH ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mch_isdir (char*) ; 
 int /*<<< orphan*/ * utf16_to_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vim_strsave (char*) ; 

__attribute__((used)) static int
executable_exists(char *name, char_u **path)
{
    char	*dum;
    char	fname[_MAX_PATH];

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR	*p = enc_to_utf16(name, NULL);
	WCHAR	fnamew[_MAX_PATH];
	WCHAR	*dumw;
	long	n;

	if (p != NULL)
	{
	    n = (long)SearchPathW(NULL, p, NULL, _MAX_PATH, fnamew, &dumw);
	    vim_free(p);
	    if (n > 0 || GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
	    {
		if (n == 0)
		    return FALSE;
		if (GetFileAttributesW(fnamew) & FILE_ATTRIBUTE_DIRECTORY)
		    return FALSE;
		if (path != NULL)
		    *path = utf16_to_enc(fnamew, NULL);
		return TRUE;
	    }
	    /* Retry with non-wide function (for Windows 98). */
	}
    }
#endif
    if (SearchPath(NULL, name, NULL, _MAX_PATH, fname, &dum) == 0)
	return FALSE;
    if (mch_isdir(fname))
	return FALSE;
    if (path != NULL)
	*path = vim_strsave(fname);
    return TRUE;
}