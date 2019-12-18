#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_id ;
struct TYPE_7__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_8__ {TYPE_1__ stub_features; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ libgdbr_t ;

/* Variables and functions */
 char* CMD_C_STEP ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_2__*) ; 
 char* sdb_fmt (char*,int) ; 
 int send_vcont (TYPE_2__*,char*,char*) ; 
 scalar_t__ write_thread_id (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int gdbr_step(libgdbr_t *g, int tid) {
	int ret = -1;
	char thread_id[64] = { 0 };

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	if (tid <= 0 || write_thread_id (thread_id, sizeof (thread_id) - 1, g->pid, tid,
		    g->stub_features.multiprocess) < 0) {
		send_vcont (g, "vCont?", NULL);
		send_vcont (g, sdb_fmt ("Hc%d", tid), NULL);
		ret = send_vcont (g, CMD_C_STEP, NULL);
		goto end;
	}

	ret = send_vcont (g, CMD_C_STEP, thread_id);
end:
	gdbr_lock_leave (g);
	return ret;
}