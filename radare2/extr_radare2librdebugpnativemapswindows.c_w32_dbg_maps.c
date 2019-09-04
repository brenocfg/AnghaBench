#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  mbi ;
struct TYPE_17__ {scalar_t__ State; int Type; scalar_t__ RegionSize; scalar_t__ BaseAddress; } ;
struct TYPE_16__ {int /*<<< orphan*/  pid; } ;
struct TYPE_15__ {int /*<<< orphan*/  sect_hdr; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {scalar_t__ lpMinimumApplicationAddress; scalar_t__ lpMaximumApplicationAddress; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  TYPE_2__ RWinModInfo ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_3__ RDebug ;
typedef  TYPE_4__ MEMORY_BASIC_INFORMATION ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 scalar_t__ MEM_FREE ; 
#define  MEM_IMAGE 129 
#define  MEM_MAPPED 128 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_VM_READ ; 
 scalar_t__ VirtualQueryEx (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*,int) ; 
 int /*<<< orphan*/  add_map_reg (int /*<<< orphan*/ *,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_mem_img (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  proc_mem_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  w32_OpenProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * w32_dbg_modules (TYPE_3__*) ; 

__attribute__((used)) static RList *w32_dbg_maps(RDebug *dbg) {
	SYSTEM_INFO si = {0};
	LPVOID cur_addr;
	MEMORY_BASIC_INFORMATION mbi;
	HANDLE h_proc;
	RWinModInfo mod_inf = {0};
	RList *map_list = r_list_new(), *mod_list = NULL;

	GetSystemInfo (&si);
	h_proc = w32_OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dbg->pid);
	if (!h_proc) {
		r_sys_perror ("w32_dbg_maps/w32_OpenProcess");
		goto err_w32_dbg_maps;
	}
	cur_addr = si.lpMinimumApplicationAddress;
	/* get process modules list */
	mod_list = w32_dbg_modules (dbg);
	/* process memory map */
	while (cur_addr < si.lpMaximumApplicationAddress &&
		VirtualQueryEx (h_proc, cur_addr, &mbi, sizeof (mbi)) != 0) {
		if (mbi.State != MEM_FREE) {
			switch (mbi.Type) {
			case MEM_IMAGE:
				proc_mem_img (h_proc, map_list, mod_list, &mod_inf, &si, &mbi);
				break;
			case MEM_MAPPED:
				proc_mem_map (h_proc, map_list, &mbi);
				break;
			default:
				add_map_reg (map_list, "", &mbi);
			}
		}
		cur_addr = (LPVOID)(size_t)((ut64)(size_t)mbi.BaseAddress + mbi.RegionSize);
	}
err_w32_dbg_maps:
	free (mod_inf.sect_hdr);
	r_list_free (mod_list);
	return map_list;
}