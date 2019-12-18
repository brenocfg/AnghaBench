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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FormatMessageW (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int LoadStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

DWORD
FormatString(
	DWORD dwFlags,
	HINSTANCE hInstance,
	DWORD dwStringId,
	DWORD dwLanguageId,
	LPWSTR lpBuffer,
	DWORD nSize,
	va_list* Arguments
)
{
	DWORD dwRet;
	int len;
	WCHAR Buffer[1000];

	len = LoadStringW(hInstance, dwStringId, (LPWSTR)Buffer, 1000);

	if (len)
	{
		dwFlags |= FORMAT_MESSAGE_FROM_STRING;
		dwFlags &= ~(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM);
		dwRet = FormatMessageW(dwFlags, Buffer, 0, dwLanguageId, lpBuffer, nSize, Arguments);
		return dwRet;
	}
	return 0;
}