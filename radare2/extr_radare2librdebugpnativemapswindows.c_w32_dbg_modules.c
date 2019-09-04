#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_11__ {int dwSize; int /*<<< orphan*/  szExePath; scalar_t__ modBaseSize; int /*<<< orphan*/  szModule; scalar_t__ modBaseAddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid; } ;
struct TYPE_9__ {void* file; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RDebugMap ;
typedef  TYPE_2__ RDebug ;
typedef  TYPE_3__ MODULEENTRY32 ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  Module32First (scalar_t__,TYPE_3__*) ; 
 scalar_t__ Module32Next (scalar_t__,TYPE_3__*) ; 
 int TH32CS_SNAPMODULE ; 
 int TH32CS_SNAPMODULE32 ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* r_debug_map_new (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 void* r_sys_conv_win_to_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ w32_CreateToolhelp32Snapshot (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList *w32_dbg_modules(RDebug *dbg) {
	MODULEENTRY32 me32;
	RDebugMap *mr;
	RList *list = r_list_new ();
	DWORD flags = TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32;
	HANDLE h_mod_snap = w32_CreateToolhelp32Snapshot (flags, dbg->pid);

	if (!h_mod_snap) {
		r_sys_perror ("w32_dbg_modules/CreateToolhelp32Snapshot");
		goto err_w32_dbg_modules;
	}
	me32.dwSize = sizeof (MODULEENTRY32);
	if (!Module32First (h_mod_snap, &me32)) {
		goto err_w32_dbg_modules;
	}
	do {
		char *mod_name;
		ut64 baddr = (ut64)(size_t)me32.modBaseAddr;

		mod_name = r_sys_conv_win_to_utf8 (me32.szModule);
		mr = r_debug_map_new (mod_name, baddr, baddr + me32.modBaseSize, 0, 0);
		free (mod_name);
		if (mr) {
			mr->file = r_sys_conv_win_to_utf8 (me32.szExePath);
			if (mr->file) {
				r_list_append (list, mr);
			}
		}
	} while (Module32Next (h_mod_snap, &me32));
err_w32_dbg_modules:
	if (h_mod_snap) {
		CloseHandle (h_mod_snap);
	}
	return list;
}