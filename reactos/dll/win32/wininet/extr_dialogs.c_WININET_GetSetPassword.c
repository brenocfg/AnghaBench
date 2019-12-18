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
typedef  int WORD ;
typedef  char WCHAR ;
typedef  int UINT ;
typedef  char* LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IDC_PASSWORD ; 
 int /*<<< orphan*/  IDC_USERNAME ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 scalar_t__ WN_SUCCESS ; 
 scalar_t__ WNetCachePassword (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WNetGetCachedPassword (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 char* strchrW (char*,char) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL WININET_GetSetPassword( HWND hdlg, LPCWSTR szServer, 
                                    LPCWSTR szRealm, BOOL bSet )
{
    WCHAR szResource[0x80], szUserPass[0x40];
    LPWSTR p;
    HWND hUserItem, hPassItem;
    DWORD r, dwMagic = 19;
    UINT r_len, u_len;
    WORD sz;
    static const WCHAR szColon[] = { ':',0 };
    static const WCHAR szbs[] = { '/', 0 };

    hUserItem = GetDlgItem( hdlg, IDC_USERNAME );
    hPassItem = GetDlgItem( hdlg, IDC_PASSWORD );

    /* now try fetch the username and password */
    lstrcpyW( szResource, szServer);
    lstrcatW( szResource, szbs);
    lstrcatW( szResource, szRealm);

    /*
     * WNetCachePassword is only concerned with the length
     * of the data stored (which we tell it) and it does
     * not use strlen() internally so we can add WCHAR data
     * instead of ASCII data and get it back the same way.
     */
    if( bSet )
    {
        szUserPass[0] = 0;
        GetWindowTextW( hUserItem, szUserPass, 
                        (sizeof szUserPass-1)/sizeof(WCHAR) );
        lstrcatW(szUserPass, szColon);
        u_len = strlenW( szUserPass );
        GetWindowTextW( hPassItem, szUserPass+u_len, 
                        (sizeof szUserPass)/sizeof(WCHAR)-u_len );

        r_len = (strlenW( szResource ) + 1)*sizeof(WCHAR);
        u_len = (strlenW( szUserPass ) + 1)*sizeof(WCHAR);
        r = WNetCachePassword( (CHAR*)szResource, r_len,
                               (CHAR*)szUserPass, u_len, dwMagic, 0 );

        return ( r == WN_SUCCESS );
    }

    sz = sizeof szUserPass;
    r_len = (strlenW( szResource ) + 1)*sizeof(WCHAR);
    r = WNetGetCachedPassword( (CHAR*)szResource, r_len,
                               (CHAR*)szUserPass, &sz, dwMagic );
    if( r != WN_SUCCESS )
        return FALSE;

    p = strchrW( szUserPass, ':' );
    if( p )
    {
        *p = 0;
        SetWindowTextW( hUserItem, szUserPass );
        SetWindowTextW( hPassItem, p+1 );
    }

    return TRUE;
}