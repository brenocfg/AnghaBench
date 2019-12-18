#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* szExeFile; int /*<<< orphan*/  th32ProcessID; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  RDebugPid ;
typedef  TYPE_1__ PROCESSENTRY32 ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_debug_pid_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 char* r_sys_conv_win_to_utf8 (char*) ; 
 scalar_t__ w32_OpenProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w32_QueryFullProcessImageName (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RDebugPid *build_debug_pid(PROCESSENTRY32 *pe) {
	TCHAR image_name[MAX_PATH + 1];
	DWORD length = MAX_PATH;
	RDebugPid *ret;
	char *name;
	HANDLE process = w32_OpenProcess (0x1000, //PROCESS_QUERY_LIMITED_INFORMATION,
		FALSE, pe->th32ProcessID);

	*image_name = '\0';
	if (process) {
		if (w32_QueryFullProcessImageName) {
			w32_QueryFullProcessImageName (process, 0, image_name, &length);
		}
		CloseHandle(process);
	}
	if (*image_name) {
		name = r_sys_conv_win_to_utf8 (image_name);
	} else {
		name = r_sys_conv_win_to_utf8 (pe->szExeFile);
	}
	ret = r_debug_pid_new (name, pe->th32ProcessID, 0, 's', 0);
	free (name);
	return ret;
}