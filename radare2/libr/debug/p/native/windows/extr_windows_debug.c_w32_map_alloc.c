#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {TYPE_2__* user; } ;
struct TYPE_7__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_8__ {TYPE_1__ pi; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  TYPE_2__ RIOW32Dbg ;
typedef  int /*<<< orphan*/  RDebugMap ;
typedef  TYPE_3__ RDebug ;
typedef  scalar_t__ LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 scalar_t__ VirtualAllocEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_debug_map_get (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  r_debug_map_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 

RDebugMap *w32_map_alloc(RDebug *dbg, ut64 addr, int size) {
	RIOW32Dbg *rio = dbg->user;
	LPVOID base = VirtualAllocEx (rio->pi.hProcess, (LPVOID)addr, (SIZE_T)size, MEM_COMMIT, PAGE_READWRITE);
	if (!base) {
		r_sys_perror ("w32_map_alloc/VirtualAllocEx");
		return NULL;
	}
	r_debug_map_sync (dbg);
	return r_debug_map_get (dbg, (ut64)base);
}