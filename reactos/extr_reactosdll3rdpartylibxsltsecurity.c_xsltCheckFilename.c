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

__attribute__((used)) static int
xsltCheckFilename (const char *path)
{
#ifdef HAVE_STAT
    struct stat stat_buffer;
#if defined(_WIN32) && !defined(__CYGWIN__)
    DWORD dwAttrs;

    dwAttrs = GetFileAttributes(path);
    if (dwAttrs != INVALID_FILE_ATTRIBUTES) {
        if (dwAttrs & FILE_ATTRIBUTE_DIRECTORY) {
            return 2;
		}
    }
#endif

    if (stat(path, &stat_buffer) == -1)
        return 0;

#ifdef S_ISDIR
    if (S_ISDIR(stat_buffer.st_mode)) {
        return 2;
    }
#endif
#endif
    return 1;
}