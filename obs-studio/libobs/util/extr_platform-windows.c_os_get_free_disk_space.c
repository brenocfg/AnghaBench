#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  GetDiskFreeSpaceExW (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

uint64_t os_get_free_disk_space(const char *dir)
{
	wchar_t *wdir = NULL;
	if (!os_utf8_to_wcs_ptr(dir, 0, &wdir))
		return 0;

	ULARGE_INTEGER free;
	bool success = !!GetDiskFreeSpaceExW(wdir, &free, NULL, NULL);
	bfree(wdir);

	return success ? free.QuadPart : 0;
}