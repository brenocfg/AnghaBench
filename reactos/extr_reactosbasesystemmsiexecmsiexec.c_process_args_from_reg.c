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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InstallRunOnce ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  process_args (char*,int*,char***) ; 

__attribute__((used)) static BOOL process_args_from_reg( const WCHAR *ident, int *pargc, WCHAR ***pargv )
{
	LONG r;
	HKEY hkey;
	DWORD sz = 0, type = 0;
	WCHAR *buf;
	BOOL ret = FALSE;

	r = RegOpenKeyW(HKEY_LOCAL_MACHINE, InstallRunOnce, &hkey);
	if(r != ERROR_SUCCESS)
		return FALSE;
	r = RegQueryValueExW(hkey, ident, 0, &type, 0, &sz);
	if(r == ERROR_SUCCESS && type == REG_SZ)
	{
		int len = lstrlenW( *pargv[0] );
		if (!(buf = HeapAlloc( GetProcessHeap(), 0, sz + (len + 1) * sizeof(WCHAR) )))
		{
			RegCloseKey( hkey );
			return FALSE;
		}
		memcpy( buf, *pargv[0], len * sizeof(WCHAR) );
		buf[len++] = ' ';
		r = RegQueryValueExW(hkey, ident, 0, &type, (LPBYTE)(buf + len), &sz);
		if( r == ERROR_SUCCESS )
		{
			process_args(buf, pargc, pargv);
			ret = TRUE;
		}
		HeapFree(GetProcessHeap(), 0, buf);
	}
	RegCloseKey(hkey);
	return ret;
}