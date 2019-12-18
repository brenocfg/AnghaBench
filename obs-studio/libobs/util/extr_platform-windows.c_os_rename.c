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
 int /*<<< orphan*/  MOVEFILE_REPLACE_EXISTING ; 
 scalar_t__ MoveFileExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int os_rename(const char *old_path, const char *new_path)
{
	wchar_t *old_path_utf16 = NULL;
	wchar_t *new_path_utf16 = NULL;
	int code = -1;

	if (!os_utf8_to_wcs_ptr(old_path, 0, &old_path_utf16)) {
		return -1;
	}
	if (!os_utf8_to_wcs_ptr(new_path, 0, &new_path_utf16)) {
		goto error;
	}

	code = MoveFileExW(old_path_utf16, new_path_utf16,
			   MOVEFILE_REPLACE_EXISTING)
		       ? 0
		       : -1;

error:
	bfree(old_path_utf16);
	bfree(new_path_utf16);
	return code;
}