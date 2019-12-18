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
struct TYPE_8__ {int pid; int tid; } ;
struct TYPE_9__ {int is_valid; TYPE_2__ thread; int /*<<< orphan*/  reason; } ;
struct TYPE_7__ {scalar_t__ multiprocess; } ;
struct TYPE_10__ {int pid; int data_len; TYPE_3__ stop_reason; int /*<<< orphan*/ * data; TYPE_1__ stub_features; } ;
typedef  TYPE_4__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_DEBUG_REASON_DEAD ; 
 int /*<<< orphan*/  eprintf (char*,int,...) ; 
 int gdbr_disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  isxdigit (int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ *,char*,int*,int*) ; 
 scalar_t__ strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int stop_reason_exit(libgdbr_t *g) {
	int status = 0, pid = g->pid;
	g->stop_reason.reason = R_DEBUG_REASON_DEAD;
	if (g->stub_features.multiprocess && g->data_len > 3) {
		if (sscanf (g->data + 1, "%x;process:%x", &status, &pid) != 2) {
			eprintf ("Message from remote: %s\n", g->data);
			return -1;
		}
		eprintf ("Process %d exited with status %d\n", pid, status);
		g->stop_reason.thread.pid = pid;
		g->stop_reason.thread.tid = pid;
		g->stop_reason.is_valid = true;
		return 0;
	}
	if (!isxdigit (g->data[1])) {
		eprintf ("Message from remote: %s\n", g->data);
		return -1;
	}
	status = (int) strtol (g->data + 1, NULL, 16);
	eprintf ("Process %d exited with status %d\n", g->pid, status);
	g->stop_reason.thread.pid = pid;
	g->stop_reason.thread.tid = pid;
	g->stop_reason.is_valid = true;
	// Just to be sure, disconnect
	return gdbr_disconnect (g);
}