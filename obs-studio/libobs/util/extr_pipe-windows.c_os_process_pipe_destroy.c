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
struct TYPE_4__ {int /*<<< orphan*/  process; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ os_process_pipe_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 

int os_process_pipe_destroy(os_process_pipe_t *pp)
{
	int ret = 0;

	if (pp) {
		DWORD code;

		CloseHandle(pp->handle);
		CloseHandle(pp->handle_err);

		WaitForSingleObject(pp->process, INFINITE);
		if (GetExitCodeProcess(pp->process, &code))
			ret = (int)code;

		CloseHandle(pp->process);
		bfree(pp);
	}

	return ret;
}