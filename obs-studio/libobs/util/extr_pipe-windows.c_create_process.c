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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  si ;
struct TYPE_6__ {int /*<<< orphan*/  hThread; void* hProcess; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int cb; int dwFlags; void* hStdError; void* hStdOutput; void* hStdInput; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  void* HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NO_WINDOW ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int STARTF_FORCEOFFFEEDBACK ; 
 int STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static inline bool create_process(const char *cmd_line, HANDLE stdin_handle,
				  HANDLE stdout_handle, HANDLE stderr_handle,
				  HANDLE *process)
{
	PROCESS_INFORMATION pi = {0};
	wchar_t *cmd_line_w = NULL;
	STARTUPINFOW si = {0};
	bool success = false;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_FORCEOFFFEEDBACK;
	si.hStdInput = stdin_handle;
	si.hStdOutput = stdout_handle;
	si.hStdError = stderr_handle;

	os_utf8_to_wcs_ptr(cmd_line, 0, &cmd_line_w);
	if (cmd_line_w) {
		success = !!CreateProcessW(NULL, cmd_line_w, NULL, NULL, true,
					   CREATE_NO_WINDOW, NULL, NULL, &si,
					   &pi);

		if (success) {
			*process = pi.hProcess;
			CloseHandle(pi.hThread);
		}

		bfree(cmd_line_w);
	}

	return success;
}