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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  void** PBOOL ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,char*) ; 
 void* kull_m_string_args_byName (int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_string_args_bool_byName(int argc, wchar_t * argv[], LPCWSTR name, PBOOL value) // TRUE when name exist (not value related)
{
	BOOL status = FALSE;
	LPCWSTR szData;
	if(status = kull_m_string_args_byName(argc, argv, name, &szData, NULL))
	{
		if((_wcsicmp(szData, L"on") == 0) || (_wcsicmp(szData, L"true") == 0) || (_wcsicmp(szData, L"1") == 0))
			*value = TRUE;
		else if((_wcsicmp(szData, L"off") == 0) || (_wcsicmp(szData, L"false") == 0) || (_wcsicmp(szData, L"0") == 0))
			*value = FALSE;
		else PRINT_ERROR(L"%s argument need on/true/1 or off/false/0\n", name);
	}
	return status;
}