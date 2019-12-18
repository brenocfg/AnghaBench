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
struct dstr {char* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_init_move_array (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,size_t) ; 
 int /*<<< orphan*/  os_wcs_to_utf8_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 char* strrchr (char*,char) ; 

char *os_get_executable_path_ptr(const char *name)
{
	char *ptr;
	char *slash;
	wchar_t path_utf16[MAX_PATH];
	struct dstr path;

	GetModuleFileNameW(NULL, path_utf16, MAX_PATH);

	os_wcs_to_utf8_ptr(path_utf16, 0, &ptr);
	dstr_init_move_array(&path, ptr);
	dstr_replace(&path, "\\", "/");
	slash = strrchr(path.array, '/');
	if (slash) {
		size_t len = slash - path.array + 1;
		dstr_resize(&path, len);
	}

	if (name && *name) {
		dstr_cat(&path, name);
	}

	return path.array;
}