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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int MG_MAX_PATH ; 
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  to_wchar (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

FILE *mg_fopen(const char *path, const char *mode) {
#ifdef _WIN32
  wchar_t wpath[MG_MAX_PATH], wmode[10];
  to_wchar(path, wpath, ARRAY_SIZE(wpath));
  to_wchar(mode, wmode, ARRAY_SIZE(wmode));
  return _wfopen(wpath, wmode);
#else
  return fopen(path, mode);
#endif
}