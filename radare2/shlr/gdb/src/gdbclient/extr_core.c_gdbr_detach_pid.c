#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid ;
struct TYPE_12__ {int is_valid; } ;
struct TYPE_11__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; int /*<<< orphan*/  pid; TYPE_2__ stop_reason; TYPE_1__ stub_features; int /*<<< orphan*/  sock; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_14__ {int valid; } ;

/* Variables and functions */
 char* CMD_DETACH_MP ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_3__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_3__*) ; 
 int /*<<< orphan*/  read_packet (TYPE_3__*,int) ; 
 TYPE_6__ reg_cache ; 
 int send_ack (TYPE_3__*) ; 
 int send_msg (TYPE_3__*,char*) ; 
 scalar_t__ snprintf (char*,size_t,char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int gdbr_detach_pid(libgdbr_t *g, int pid) {
	char *cmd = NULL;
	int ret = -1;
	size_t buffer_size;

	if (!g || !g->sock || !g->stub_features.multiprocess) {
		return -1;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	reg_cache.valid = false;
	g->stop_reason.is_valid = false;

	buffer_size = strlen (CMD_DETACH_MP) + (sizeof (pid) * 2) + 1;
	cmd = calloc (buffer_size, sizeof (char));
	if (!cmd) {
		ret = -1;
		goto end;
	}

	if ((snprintf (cmd, buffer_size, "%s%x", CMD_DETACH_MP, g->pid)) < 0) {
		ret = -1;
		goto end;
	}

	ret = send_msg (g, cmd);
	if (ret < 0) {
		goto end;
	}

	read_packet (g, false);
	if ((ret = send_ack (g)) < 0) {
		goto end;
	}

	if (strncmp (g->data, "OK", 2)) {
		ret = -1;
		goto end;
	}

	ret = 0;
end:
	if (cmd) {
		free (cmd);
	}
	gdbr_lock_leave (g);
	return ret;
}