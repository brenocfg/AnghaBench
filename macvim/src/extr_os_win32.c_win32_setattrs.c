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
 scalar_t__ GetACP () ; 
 scalar_t__ GetLastError () ; 
 int SetFileAttributes (char*,int) ; 
 int SetFileAttributesW (int /*<<< orphan*/ *,int) ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
    int
win32_setattrs(char_u *name, int attrs)
{
    int res;
#ifdef FEAT_MBYTE
    WCHAR	*p = NULL;

    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
	p = enc_to_utf16(name, NULL);

    if (p != NULL)
    {
	res = SetFileAttributesW(p, attrs);
	if (res == FALSE
	    && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
	{
	    /* Retry with non-wide function (for Windows 98). */
	    vim_free(p);
	    p = NULL;
	}
    }
    if (p == NULL)
#endif
	res = SetFileAttributes((char *)name, attrs);
#ifdef FEAT_MBYTE
    vim_free(p);
#endif
    return res ? 0 : -1;
}