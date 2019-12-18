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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetProcessImageFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PROCESS_QUERY_LIMITED_INFORMATION ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_from_wcs (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_process (int /*<<< orphan*/ ,int,scalar_t__) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

bool get_window_exe(struct dstr *name, HWND window)
{
	wchar_t wname[MAX_PATH];
	struct dstr temp = {0};
	bool success = false;
	HANDLE process = NULL;
	char *slash;
	DWORD id;

	GetWindowThreadProcessId(window, &id);
	if (id == GetCurrentProcessId())
		return false;

	process = open_process(PROCESS_QUERY_LIMITED_INFORMATION, false, id);
	if (!process)
		goto fail;

	if (!GetProcessImageFileNameW(process, wname, MAX_PATH))
		goto fail;

	dstr_from_wcs(&temp, wname);
	slash = strrchr(temp.array, '\\');
	if (!slash)
		goto fail;

	dstr_copy(name, slash + 1);
	success = true;

fail:
	if (!success)
		dstr_copy(name, "unknown");

	dstr_free(&temp);
	CloseHandle(process);
	return true;
}