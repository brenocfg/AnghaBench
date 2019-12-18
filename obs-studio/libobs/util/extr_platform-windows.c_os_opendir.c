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
struct os_dir {int first; int /*<<< orphan*/  wfd; int /*<<< orphan*/  handle; } ;
struct dstr {int /*<<< orphan*/  len; int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  struct os_dir os_dir_t ;
typedef  int /*<<< orphan*/  WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FindFirstFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 struct os_dir* bzalloc (int) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 scalar_t__ os_utf8_to_wcs_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

os_dir_t *os_opendir(const char *path)
{
	struct dstr path_str = {0};
	struct os_dir *dir = NULL;
	WIN32_FIND_DATA wfd;
	HANDLE handle;
	wchar_t *w_path;

	dstr_copy(&path_str, path);
	dstr_cat(&path_str, "/*.*");

	if (os_utf8_to_wcs_ptr(path_str.array, path_str.len, &w_path) > 0) {
		handle = FindFirstFileW(w_path, &wfd);
		if (handle != INVALID_HANDLE_VALUE) {
			dir = bzalloc(sizeof(struct os_dir));
			dir->handle = handle;
			dir->first = true;
			dir->wfd = wfd;
		}

		bfree(w_path);
	}

	dstr_free(&path_str);

	return dir;
}