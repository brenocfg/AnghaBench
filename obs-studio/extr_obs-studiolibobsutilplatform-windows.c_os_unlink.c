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
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int os_unlink(const char *path)
{
	wchar_t *w_path;
	bool success;

	os_utf8_to_wcs_ptr(path, 0, &w_path);
	if (!w_path)
		return -1;

	success = !!DeleteFileW(w_path);
	bfree(w_path);

	return success ? 0 : -1;
}