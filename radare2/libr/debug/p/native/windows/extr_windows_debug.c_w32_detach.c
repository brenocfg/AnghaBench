#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* params; } ;
struct TYPE_10__ {int pid; TYPE_3__* user; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hProcess; } ;
struct TYPE_9__ {TYPE_2__ pi; TYPE_5__* inst; } ;
struct TYPE_7__ {int pid; int ret; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ RIOW32Dbg ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  W32_DETTACH ; 
 int /*<<< orphan*/  w32dbg_wrap_wait_ret (TYPE_5__*) ; 

int w32_detach(RDebug *dbg, int pid) {
	if (pid == -1 || dbg->pid != pid) {
		return false;
	}
	RIOW32Dbg *rio = dbg->user;
	bool ret = false;
	if (rio->pi.hProcess) {
		rio->inst->params->type = W32_DETTACH;
		rio->inst->params->pid = pid;
		w32dbg_wrap_wait_ret (rio->inst);
		ret = rio->inst->params->ret;
	}
	if (rio->pi.hProcess) {
		CloseHandle (rio->pi.hProcess);
		rio->pi.hProcess = NULL;
	}
	return ret;
}