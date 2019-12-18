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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int INJECT_ERROR_OPEN_PROCESS_FAIL ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int inject_library (scalar_t__,int /*<<< orphan*/  const*) ; 
 scalar_t__ open_process (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int inject_library_full(DWORD process_id, const wchar_t *dll)
{
	HANDLE process = open_process(PROCESS_ALL_ACCESS, false, process_id);
	int ret;

	if (process) {
		ret = inject_library(process, dll);
		CloseHandle(process);
	} else {
		ret = INJECT_ERROR_OPEN_PROCESS_FAIL;
	}

	return ret;
}