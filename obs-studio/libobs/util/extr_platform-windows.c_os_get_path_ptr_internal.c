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
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 int /*<<< orphan*/  SHGetFolderPathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_init_move_array (struct dstr*,char*) ; 
 int /*<<< orphan*/  os_wcs_to_utf8_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static char *os_get_path_ptr_internal(const char *name, int folder)
{
	char *ptr;
	wchar_t path_utf16[MAX_PATH];
	struct dstr path;

	SHGetFolderPathW(NULL, folder, NULL, SHGFP_TYPE_CURRENT, path_utf16);

	os_wcs_to_utf8_ptr(path_utf16, 0, &ptr);
	dstr_init_move_array(&path, ptr);
	dstr_cat(&path, "\\");
	dstr_cat(&path, name);
	return path.array;
}