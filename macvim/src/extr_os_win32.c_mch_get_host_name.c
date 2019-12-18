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
typedef  int /*<<< orphan*/  wszHostName ;
typedef  char char_u ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ GetACP () ; 
 int /*<<< orphan*/  GetComputerName (char*,int*) ; 
 scalar_t__ GetComputerNameW (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GetLastError () ; 
 int enc_codepage ; 
 char* utf16_to_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 int /*<<< orphan*/  vim_strncpy (char*,char*,int) ; 

void
mch_get_host_name(
    char_u	*s,
    int		len)
{
    DWORD cch = len;

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR wszHostName[256 + 1];
	DWORD wcch = sizeof(wszHostName) / sizeof(WCHAR);

	if (GetComputerNameW(wszHostName, &wcch))
	{
	    char_u  *p = utf16_to_enc(wszHostName, NULL);

	    if (p != NULL)
	    {
		vim_strncpy(s, p, len - 1);
		vim_free(p);
		return;
	    }
	}
	else if (GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
	    return;
	/* Retry with non-wide function (for Windows 98). */
    }
#endif
    if (!GetComputerName(s, &cch))
	vim_strncpy(s, "PC (Win32 Vim)", len - 1);
}