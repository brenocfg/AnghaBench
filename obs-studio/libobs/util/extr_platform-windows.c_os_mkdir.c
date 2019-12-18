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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDirectory (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ GetLastError () ; 
 int MKDIR_ERROR ; 
 int MKDIR_EXISTS ; 
 int MKDIR_SUCCESS ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int os_mkdir(const char *path)
{
	wchar_t *path_utf16;
	BOOL success;

	if (!os_utf8_to_wcs_ptr(path, 0, &path_utf16))
		return MKDIR_ERROR;

	success = CreateDirectory(path_utf16, NULL);
	bfree(path_utf16);

	if (!success)
		return (GetLastError() == ERROR_ALREADY_EXISTS) ? MKDIR_EXISTS
								: MKDIR_ERROR;

	return MKDIR_SUCCESS;
}