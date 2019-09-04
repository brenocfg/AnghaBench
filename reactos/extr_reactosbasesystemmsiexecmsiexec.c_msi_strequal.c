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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int CSTR_EQUAL ; 
 int CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL msi_strequal(LPCWSTR str1, LPCSTR str2)
{
	DWORD len, ret;
	LPWSTR strW;

	len = MultiByteToWideChar( CP_ACP, 0, str2, -1, NULL, 0);
	if( !len )
		return FALSE;
	if( lstrlenW(str1) != (len-1) )
		return FALSE;
	strW = HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR)*len);
	MultiByteToWideChar( CP_ACP, 0, str2, -1, strW, len);
	ret = CompareStringW(GetThreadLocale(), NORM_IGNORECASE, str1, len, strW, len);
	HeapFree(GetProcessHeap(), 0, strW);
	return (ret == CSTR_EQUAL);
}