#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct game_capture {int /*<<< orphan*/  injector_process; int /*<<< orphan*/  process_id; int /*<<< orphan*/  thread_id; } ;
typedef  int /*<<< orphan*/  si ;
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int cb; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_2__ PROCESS_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NO_WINDOW ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessW (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  swprintf (char*,int,char*,char*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int use_anticheat (struct game_capture*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool create_inject_process(struct game_capture *gc,
					 const char *inject_path,
					 const char *hook_dll)
{
	wchar_t *command_line_w = malloc(4096 * sizeof(wchar_t));
	wchar_t *inject_path_w;
	wchar_t *hook_dll_w;
	bool anti_cheat = use_anticheat(gc);
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	bool success = false;

	os_utf8_to_wcs_ptr(inject_path, 0, &inject_path_w);
	os_utf8_to_wcs_ptr(hook_dll, 0, &hook_dll_w);

	si.cb = sizeof(si);

	swprintf(command_line_w, 4096, L"\"%s\" \"%s\" %lu %lu", inject_path_w,
		 hook_dll_w, (unsigned long)anti_cheat,
		 anti_cheat ? gc->thread_id : gc->process_id);

	success = !!CreateProcessW(inject_path_w, command_line_w, NULL, NULL,
				   false, CREATE_NO_WINDOW, NULL, NULL, &si,
				   &pi);
	if (success) {
		CloseHandle(pi.hThread);
		gc->injector_process = pi.hProcess;
	} else {
		warn("Failed to create inject helper process: %lu",
		     GetLastError());
	}

	free(command_line_w);
	bfree(inject_path_w);
	bfree(hook_dll_w);
	return success;
}