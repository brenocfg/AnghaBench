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

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MOVEFILE_REPLACE_EXISTING ; 
 scalar_t__ MoveFileExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ReplaceFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int os_safe_replace(const char *target, const char *from, const char *backup)
{
	wchar_t *wtarget = NULL;
	wchar_t *wfrom = NULL;
	wchar_t *wbackup = NULL;
	int code = -1;

	if (!target || !from)
		return -1;
	if (!os_utf8_to_wcs_ptr(target, 0, &wtarget))
		return -1;
	if (!os_utf8_to_wcs_ptr(from, 0, &wfrom))
		goto fail;
	if (backup && !os_utf8_to_wcs_ptr(backup, 0, &wbackup))
		goto fail;

	if (ReplaceFileW(wtarget, wfrom, wbackup, 0, NULL, NULL)) {
		code = 0;
	} else if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		code = MoveFileExW(wfrom, wtarget, MOVEFILE_REPLACE_EXISTING)
			       ? 0
			       : -1;
	}

fail:
	bfree(wtarget);
	bfree(wfrom);
	bfree(wbackup);
	return code;
}