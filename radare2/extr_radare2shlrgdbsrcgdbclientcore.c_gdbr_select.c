#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int is_valid; } ;
struct TYPE_9__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_11__ {int pid; int tid; int /*<<< orphan*/  data; TYPE_2__ stop_reason; TYPE_1__ stub_features; } ;
typedef  TYPE_3__ libgdbr_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_12__ {int valid; } ;

/* Variables and functions */
 scalar_t__ read_packet (TYPE_3__*,int) ; 
 TYPE_6__ reg_cache ; 
 scalar_t__ send_ack (TYPE_3__*) ; 
 scalar_t__ send_msg (TYPE_3__*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ write_thread_id (char*,int,int,int,int /*<<< orphan*/ ) ; 

int gdbr_select(libgdbr_t *g, int pid, int tid) {
	char cmd[64] = { 0 };
	reg_cache.valid = false;
	g->pid = pid;
	g->tid = tid;
	strcpy (cmd, "Hg");
	if (write_thread_id (cmd + 2, sizeof (cmd) - 3, pid, tid,
			     g->stub_features.multiprocess) < 0) {
		return -1;
	}
	g->stop_reason.is_valid = false;
	if (send_msg (g, cmd) < 0 || read_packet (g, false) < 0 || send_ack (g) < 0) {
		return -1;
	}
	if (strcmp (g->data, "OK")) {
		return -1;
	}
	return 0;
}