#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_7__ {TYPE_2__* user; } ;
struct TYPE_5__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {TYPE_1__ pi; } ;
typedef  TYPE_2__ RIOW32Dbg ;
typedef  TYPE_3__ RDebug ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int VirtualProtectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __io_perms_to_prot (int) ; 

int w32_map_protect(RDebug *dbg, ut64 addr, int size, int perms) {
	DWORD old;
	RIOW32Dbg *rio = dbg->user;
	return VirtualProtectEx (rio->pi.hProcess, (LPVOID)(size_t)addr,
		size, __io_perms_to_prot (perms), &old);
}