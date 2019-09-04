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
struct TYPE_4__ {int /*<<< orphan*/  BaseAddress; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  add_map_reg (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_sys_conv_win_to_utf8 (int /*<<< orphan*/ *) ; 
 scalar_t__ w32_GetMappedFileName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_mem_map(HANDLE h_proc, RList *map_list, MEMORY_BASIC_INFORMATION *mbi) {
	TCHAR f_name[MAX_PATH + 1];

	DWORD len = w32_GetMappedFileName (h_proc, mbi->BaseAddress, f_name, MAX_PATH);
	if (len > 0) {
		char *f_name_ = r_sys_conv_win_to_utf8 (f_name);
		add_map_reg (map_list, f_name_, mbi);
		free (f_name_);
	} else {
		add_map_reg (map_list, "", mbi);
	}
}