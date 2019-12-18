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
typedef  int wchar_t ;
struct dstr {int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  void* HMODULE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_PROC_NOT_FOUND ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageA (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LOG_INFO ; 
 void* LoadLibraryW (int*) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SetDllDirectoryW (int*) ; 
 int /*<<< orphan*/  bfree (int*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_find (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**) ; 
 int* wcsrchr (int*,int) ; 

void *os_dlopen(const char *path)
{
	struct dstr dll_name;
	wchar_t *wpath;
	wchar_t *wpath_slash;
	HMODULE h_library = NULL;

	if (!path)
		return NULL;

	dstr_init_copy(&dll_name, path);
	dstr_replace(&dll_name, "\\", "/");
	if (!dstr_find(&dll_name, ".dll"))
		dstr_cat(&dll_name, ".dll");

	os_utf8_to_wcs_ptr(dll_name.array, 0, &wpath);

	/* to make module dependency issues easier to deal with, allow
	 * dynamically loaded libraries on windows to search for dependent
	 * libraries that are within the library's own directory */
	wpath_slash = wcsrchr(wpath, L'/');
	if (wpath_slash) {
		*wpath_slash = 0;
		SetDllDirectoryW(wpath);
		*wpath_slash = L'/';
	}

	h_library = LoadLibraryW(wpath);
	bfree(wpath);
	dstr_free(&dll_name);

	if (wpath_slash)
		SetDllDirectoryW(NULL);

	if (!h_library) {
		DWORD error = GetLastError();

		/* don't print error for libraries that aren't meant to be
		 * dynamically linked */
		if (error == ERROR_PROC_NOT_FOUND)
			return NULL;

		char *message = NULL;

		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
				       FORMAT_MESSAGE_IGNORE_INSERTS |
				       FORMAT_MESSAGE_ALLOCATE_BUFFER,
			       NULL, error,
			       MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			       (LPSTR)&message, 0, NULL);

		blog(LOG_INFO, "LoadLibrary failed for '%s': %s (%lu)", path,
		     message, error);

		if (message)
			LocalFree(message);
	}

	return h_library;
}