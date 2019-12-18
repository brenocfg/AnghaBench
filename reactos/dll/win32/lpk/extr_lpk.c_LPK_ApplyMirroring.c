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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int GetFileVersionInfoSizeW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileVersionInfoW (char*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetUserDefaultLangID () ; 
 int /*<<< orphan*/  HIWORD (int) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int LAYOUT_RTL ; 
 scalar_t__ LOWORD (int) ; 
 scalar_t__ MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PRIMARYLANGID (int) ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/  SetProcessDefaultLayout (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VerQueryValueW (void*,char const*,void**,int*) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LPK_ApplyMirroring()
{
    static const WCHAR translationW[] = { '\\','V','a','r','F','i','l','e','I','n','f','o',
                                          '\\','T','r','a','n','s','l','a','t','i','o','n', 0 };
    static const WCHAR filedescW[] = { '\\','S','t','r','i','n','g','F','i','l','e','I','n','f','o',
                                       '\\','%','0','4','x','%','0','4','x',
                                       '\\','F','i','l','e','D','e','s','c','r','i','p','t','i','o','n',0 };
    WCHAR *str, buffer[MAX_PATH];
#ifdef __REACTOS__
    DWORD i, version_layout = 0;
    UINT len;
#else
    DWORD i, len, version_layout = 0;
#endif
    DWORD user_lang = GetUserDefaultLangID();
    DWORD *languages;
    void *data = NULL;

    GetModuleFileNameW( 0, buffer, MAX_PATH );
    if (!(len = GetFileVersionInfoSizeW( buffer, NULL ))) goto done;
    if (!(data = HeapAlloc( GetProcessHeap(), 0, len ))) goto done;
    if (!GetFileVersionInfoW( buffer, 0, len, data )) goto done;
    if (!VerQueryValueW( data, translationW, (void **)&languages, &len ) || !len) goto done;

    len /= sizeof(DWORD);
    for (i = 0; i < len; i++) if (LOWORD(languages[i]) == user_lang) break;
    if (i == len)  /* try neutral language */
    for (i = 0; i < len; i++)
        if (LOWORD(languages[i]) == MAKELANGID( PRIMARYLANGID(user_lang), SUBLANG_NEUTRAL )) break;
    if (i == len) i = 0;  /* default to the first one */

    sprintfW( buffer, filedescW, LOWORD(languages[i]), HIWORD(languages[i]) );
    if (!VerQueryValueW( data, buffer, (void **)&str, &len )) goto done;
    TRACE( "found description %s\n", debugstr_w( str ));
    if (str[0] == 0x200e && str[1] == 0x200e) version_layout = LAYOUT_RTL;

done:
    HeapFree( GetProcessHeap(), 0, data );
    SetProcessDefaultLayout(version_layout);
}