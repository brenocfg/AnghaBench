#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* system ) (int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_flush () ; 
 char* sdb_fmt (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool __io_kill(RDebug *dbg, int pid, int tid, int sig) {
	const char *cmd = sdb_fmt ("dk %d", sig);
	dbg->iob.system (dbg->iob.io, cmd);
	r_cons_flush ();
	return true;
}