#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct os_dirent {int /*<<< orphan*/  directory; int /*<<< orphan*/  d_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  cFileName; } ;
struct TYPE_5__ {int first; struct os_dirent out; TYPE_3__ wfd; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ os_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindNextFileW (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  is_dir (TYPE_3__*) ; 
 int /*<<< orphan*/  os_wcs_to_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct os_dirent *os_readdir(os_dir_t *dir)
{
	if (!dir)
		return NULL;

	if (dir->first) {
		dir->first = false;
	} else {
		if (!FindNextFileW(dir->handle, &dir->wfd))
			return NULL;
	}

	os_wcs_to_utf8(dir->wfd.cFileName, 0, dir->out.d_name,
		       sizeof(dir->out.d_name));

	dir->out.directory = is_dir(&dir->wfd);

	return &dir->out;
}