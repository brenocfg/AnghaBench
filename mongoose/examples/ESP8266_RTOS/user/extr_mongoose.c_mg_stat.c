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
typedef  int /*<<< orphan*/  cs_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int MG_MAX_PATH ; 
 int _wstati64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_wchar (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mg_stat(const char *path, cs_stat_t *st) {
#ifdef _WIN32
  wchar_t wpath[MG_MAX_PATH];
  to_wchar(path, wpath, ARRAY_SIZE(wpath));
  DBG(("[%ls] -> %d", wpath, _wstati64(wpath, st)));
  return _wstati64(wpath, st);
#else
  return stat(path, st);
#endif
}