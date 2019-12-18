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
typedef  char wchar_t ;
struct win_version_info {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int) ; 
 int /*<<< orphan*/  GetSystemWow64DirectoryW (char*,int) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int get_dll_ver (char*,struct win_version_info*) ; 
 int /*<<< orphan*/  wcscat (char*,char const*) ; 

__attribute__((used)) static bool get_32bit_system_dll_ver(const wchar_t *system_lib,
				     struct win_version_info *ver)
{
	wchar_t path[MAX_PATH];
	UINT ret;

#ifdef _WIN64
	ret = GetSystemWow64DirectoryW(path, MAX_PATH);
#else
	ret = GetSystemDirectoryW(path, MAX_PATH);
#endif
	if (!ret) {
		blog(LOG_ERROR,
		     "Failed to get windows 32bit system path: "
		     "%lu",
		     GetLastError());
		return false;
	}

	wcscat(path, L"\\");
	wcscat(path, system_lib);
	return get_dll_ver(path, ver);
}