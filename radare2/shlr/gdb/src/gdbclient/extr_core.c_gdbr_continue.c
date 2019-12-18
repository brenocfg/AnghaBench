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
typedef  int /*<<< orphan*/  command ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_C_CONT ; 
 char* CMD_C_CONT_SIG ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_2__*) ; 
 int send_vcont (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ write_thread_id (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int gdbr_continue(libgdbr_t *g, int pid, int tid, int sig) {
	char thread_id[64] = { 0 };
	char command[16] = { 0 };
	int ret = -1;

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	if (sig <= 0) {
		strncpy (command, CMD_C_CONT, sizeof (command) - 1);
	} else {
		snprintf (command, sizeof (command) - 1, "%s%02x", CMD_C_CONT_SIG, sig);
	}
	if (tid <= 0 || write_thread_id (thread_id, sizeof (thread_id) - 1, g->pid, tid,
		    g->stub_features.multiprocess) < 0) {
		ret = send_vcont (g, command, NULL);
		goto end;
	}

	ret = send_vcont (g, command, thread_id);
end:
	gdbr_lock_leave (g);
	return ret;
}