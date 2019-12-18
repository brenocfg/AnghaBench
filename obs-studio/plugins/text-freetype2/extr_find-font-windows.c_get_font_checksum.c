#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dstr {int len; int /*<<< orphan*/ * array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cFileName; int /*<<< orphan*/  ftLastWriteTime; } ;
typedef  TYPE_1__ WIN32_FIND_DATAA ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_FONTS ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FindNextFileA (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ SHGetFolderPathA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  calc_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_reserve (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 

uint32_t get_font_checksum(void)
{
	uint32_t checksum = 0;
	struct dstr path = {0};
	HANDLE handle;
	WIN32_FIND_DATAA wfd;

	dstr_reserve(&path, MAX_PATH);

	HRESULT res = SHGetFolderPathA(NULL, CSIDL_FONTS, NULL,
				       SHGFP_TYPE_CURRENT, path.array);
	if (res != S_OK) {
		blog(LOG_WARNING, "Error finding windows font folder");
		return 0;
	}

	path.len = strlen(path.array);
	dstr_cat(&path, "\\*.*");

	handle = FindFirstFileA(path.array, &wfd);
	if (handle == INVALID_HANDLE_VALUE)
		goto free_string;

	dstr_resize(&path, path.len - 4);

	do {
		checksum = calc_crc32(checksum, &wfd.ftLastWriteTime,
				      sizeof(FILETIME));
		checksum = calc_crc32(checksum, wfd.cFileName,
				      strlen(wfd.cFileName));
	} while (FindNextFileA(handle, &wfd));

	FindClose(handle);

free_string:
	dstr_free(&path);
	return checksum;
}