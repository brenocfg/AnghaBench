#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* user; } ;
struct TYPE_9__ {int /*<<< orphan*/  exe; } ;
struct TYPE_7__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_8__ {TYPE_1__ pi; } ;
typedef  TYPE_2__ RIOW32Dbg ;
typedef  TYPE_3__ RDebugInfo ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  __resolve_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __w32_info_exe(RDebug *dbg, RDebugInfo *rdi) {
	RIOW32Dbg *rio = dbg->user;
	rdi->exe = __resolve_path (rio->pi.hProcess, NULL);
}