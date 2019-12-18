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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int MG_MAX_PATH ; 
 int _wopen (int /*<<< orphan*/ *,int,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  to_wchar (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mg_open(const char *path, int flag, int mode) { /* LCOV_EXCL_LINE */
#if defined(_WIN32) && !defined(WINCE)
  wchar_t wpath[MG_MAX_PATH];
  to_wchar(path, wpath, ARRAY_SIZE(wpath));
  return _wopen(wpath, flag, mode);
#else
  return open(path, flag, mode); /* LCOV_EXCL_LINE */
#endif
}