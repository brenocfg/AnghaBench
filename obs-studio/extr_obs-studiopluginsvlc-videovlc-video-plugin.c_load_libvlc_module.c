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

/* Variables and functions */
 int /*<<< orphan*/ * libvlc_module ; 
 int /*<<< orphan*/ * os_dlopen (char*) ; 

__attribute__((used)) static bool load_libvlc_module(void)
{
#ifdef _WIN32
	char    *path_utf8 = NULL;
	wchar_t path[1024];
	LSTATUS status;
	DWORD   size;
	HKEY    key;

	memset(path, 0, 1024 * sizeof(wchar_t));

	status = RegOpenKeyW(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\VideoLAN\\VLC",
			&key);
	if (status != ERROR_SUCCESS)
		return false;

	size = 1024;
	status = RegQueryValueExW(key, L"InstallDir", NULL, NULL,
			(LPBYTE)path, &size);
	if (status == ERROR_SUCCESS) {
		wcscat(path, L"\\libvlc.dll");
		os_wcs_to_utf8_ptr(path, 0, &path_utf8);
		libvlc_module = os_dlopen(path_utf8);
		bfree(path_utf8);
	}

	RegCloseKey(key);
#else

#ifdef __APPLE__
#define LIBVLC_DIR "/Applications/VLC.app/Contents/MacOS/"
/* According to otoolo -L, this is what libvlc.dylib wants. */
#define LIBVLC_CORE_FILE LIBVLC_DIR "lib/libvlccore.dylib"
#define LIBVLC_FILE LIBVLC_DIR "lib/libvlc.5.dylib"
	setenv("VLC_PLUGIN_PATH", LIBVLC_DIR "plugins", false);
	libvlc_core_module = os_dlopen(LIBVLC_CORE_FILE);

	if (!libvlc_core_module)
		return false;
#else
#define LIBVLC_FILE "libvlc.so.5"
#endif
	libvlc_module = os_dlopen(LIBVLC_FILE);

#endif

	return libvlc_module != NULL;
}