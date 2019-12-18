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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CommandLineToArgvW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetCommandLineW () ; 
 scalar_t__ GetModuleFileNameW (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int INJECT_ERROR_INVALID_PARAMS ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SEM_FAILCRITICALERRORS ; 
 int /*<<< orphan*/  SetErrorMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (char**) ; 
 int inject_helper (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  load_debug_privilege () ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* wcsrchr (scalar_t__*,char) ; 

int main(int argc, char *argv_ansi[])
{
	wchar_t dll_path[MAX_PATH];
	LPWSTR pCommandLineW;
	LPWSTR *argv;
	int ret = INJECT_ERROR_INVALID_PARAMS;

	SetErrorMode(SEM_FAILCRITICALERRORS);
	load_debug_privilege();

	pCommandLineW = GetCommandLineW();
	argv = CommandLineToArgvW(pCommandLineW, &argc);
	if (argv && argc == 4) {
		DWORD size = GetModuleFileNameW(NULL, dll_path, MAX_PATH);
		if (size) {
			wchar_t *name_start = wcsrchr(dll_path, '\\');
			if (name_start) {
				*(++name_start) = 0;
				wcscpy(name_start, argv[1]);
				ret = inject_helper(argv, dll_path);
			}
		}
	}
	LocalFree(argv);

	UNUSED_PARAMETER(argv_ansi);
	return ret;
}