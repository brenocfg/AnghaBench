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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 char* LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lstrlenW (char const*) ; 

__attribute__((used)) static BSTR include_pac_utils( const WCHAR *script )
{
    static const WCHAR pacjsW[] = {'p','a','c','.','j','s',0};
    HMODULE hmod = GetModuleHandleA( "jsproxy.dll" );
    HRSRC rsrc;
    DWORD size;
    const char *data;
    BSTR ret;
    int len;

    if (!(rsrc = FindResourceW( hmod, pacjsW, (LPCWSTR)40 ))) return NULL;
    size = SizeofResource( hmod, rsrc );
    data = LoadResource( hmod, rsrc );

    len = MultiByteToWideChar( CP_ACP, 0, data, size, NULL, 0 );
    if (!(ret = SysAllocStringLen( NULL, len + lstrlenW( script ) + 1 ))) return NULL;
    MultiByteToWideChar( CP_ACP, 0, data, size, ret, len );
    lstrcpyW( ret + len, script );
    return ret;
}