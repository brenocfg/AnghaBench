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
typedef  int DWORD ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ GetUserName (char*,int*) ; 
 int /*<<< orphan*/  NUL ; 
 int OK ; 
 int /*<<< orphan*/  vim_strncpy (int /*<<< orphan*/ *,char*,int) ; 

int
mch_get_user_name(
    char_u  *s,
    int	    len)
{
    char szUserName[256 + 1];	/* UNLEN is 256 */
    DWORD cch = sizeof szUserName;

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR wszUserName[256 + 1];	/* UNLEN is 256 */
	DWORD wcch = sizeof(wszUserName) / sizeof(WCHAR);

	if (GetUserNameW(wszUserName, &wcch))
	{
	    char_u  *p = utf16_to_enc(wszUserName, NULL);

	    if (p != NULL)
	    {
		vim_strncpy(s, p, len - 1);
		vim_free(p);
		return OK;
	    }
	}
	else if (GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
	    return FAIL;
	/* Retry with non-wide function (for Windows 98). */
    }
#endif
    if (GetUserName(szUserName, &cch))
    {
	vim_strncpy(s, szUserName, len - 1);
	return OK;
    }
    s[0] = NUL;
    return FAIL;
}