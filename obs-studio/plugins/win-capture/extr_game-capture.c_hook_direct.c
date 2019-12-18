#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/  executable; } ;
struct game_capture {TYPE_1__ config; int /*<<< orphan*/  process_id; } ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/ * _wfullpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int inject_library (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_process (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static inline bool hook_direct(struct game_capture *gc,
			       const char *hook_path_rel)
{
	wchar_t hook_path_abs_w[MAX_PATH];
	wchar_t *hook_path_rel_w;
	wchar_t *path_ret;
	HANDLE process;
	int ret;

	os_utf8_to_wcs_ptr(hook_path_rel, 0, &hook_path_rel_w);
	if (!hook_path_rel_w) {
		warn("hook_direct: could not convert string");
		return false;
	}

	path_ret = _wfullpath(hook_path_abs_w, hook_path_rel_w, MAX_PATH);
	bfree(hook_path_rel_w);

	if (path_ret == NULL) {
		warn("hook_direct: could not make absolute path");
		return false;
	}

	process = open_process(PROCESS_ALL_ACCESS, false, gc->process_id);
	if (!process) {
		warn("hook_direct: could not open process: %s (%lu)",
		     gc->config.executable, GetLastError());
		return false;
	}

	ret = inject_library(process, hook_path_abs_w);
	CloseHandle(process);

	if (ret != 0) {
		warn("hook_direct: inject failed: %d", ret);
		return false;
	}

	return true;
}