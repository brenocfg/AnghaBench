#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {int present; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_18__ {int present; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_16__ {char* path; int present; } ;
struct TYPE_15__ {int present; int /*<<< orphan*/  addr; } ;
struct TYPE_14__ {int present; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_13__ {int signum; int core; int is_valid; int vforkdone; int library; int swbreak; int hwbreak; int create; int /*<<< orphan*/  reason; TYPE_6__ vfork; TYPE_5__ fork; TYPE_3__ exec; TYPE_2__ watchpoint; TYPE_1__ thread; } ;
struct TYPE_17__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_20__ {int data_len; int* data; TYPE_11__ stop_reason; TYPE_4__ stub_features; } ;
typedef  TYPE_7__ libgdbr_t ;
typedef  int /*<<< orphan*/  libgdbr_stop_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_DEBUG_REASON_BREAKPOINT ; 
 int /*<<< orphan*/  R_DEBUG_REASON_NONE ; 
 int /*<<< orphan*/  R_DEBUG_REASON_SIGNAL ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 scalar_t__ read_thread_id (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ack (TYPE_7__*) ; 
 int sscanf (char*,char*,int*) ; 
 int stop_reason_exit (TYPE_7__*) ; 
 int stop_reason_terminated (TYPE_7__*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unpack_hex (char*,int,char*) ; 

int handle_stop_reason(libgdbr_t *g) {
	send_ack (g);
	if (g->data_len < 3) {
		return -1;
	}
	switch (g->data[0]) {
	case 'O':
		unpack_hex (g->data + 1, g->data_len - 1, g->data + 1);
		//g->data[g->data_len - 1] = '\0';
		eprintf ("%s", g->data + 1);
		if (send_ack (g) < 0) {
			return -1;
		}
		memset (&g->stop_reason, 0, sizeof (libgdbr_stop_reason_t));
		g->stop_reason.signum = -1;
		g->stop_reason.reason = R_DEBUG_REASON_NONE;
		return 0;
	case 'W':
		return stop_reason_exit (g);
	case 'X':
		return stop_reason_terminated (g);
	}
	if (g->data[0] != 'T') {
		return -1;
	}
	char *ptr1, *ptr2;
	g->data[g->data_len] = '\0';
	free (g->stop_reason.exec.path);
	memset (&g->stop_reason, 0, sizeof (libgdbr_stop_reason_t));
	g->stop_reason.core = -1;
	if (sscanf (g->data + 1, "%02x", &g->stop_reason.signum) != 1) {
		return -1;
	}
	g->stop_reason.is_valid = true;
	g->stop_reason.reason = R_DEBUG_REASON_SIGNAL;
	for (ptr1 = strtok (g->data + 3, ";"); ptr1; ptr1 = strtok (NULL, ";")) {
		if (r_str_startswith (ptr1, "thread") && !g->stop_reason.thread.present) {
			if (!(ptr2 = strchr (ptr1, ':'))) {
				continue;
			}
			ptr2++;
			if (read_thread_id (ptr2, &g->stop_reason.thread.pid,
					    &g->stop_reason.thread.tid,
					    g->stub_features.multiprocess) < 0) {
				continue;
			}
			g->stop_reason.thread.present = true;
			continue;
		}
		if (r_str_startswith (ptr1, "core")) {
			if (!(ptr2 = strchr (ptr1, ':'))) {
				continue;
			}
			ptr2++;
			if (!isxdigit (*ptr2)) {
				continue;
			}
			g->stop_reason.core = (int) strtol (ptr2, NULL, 16);
			continue;
		}
		if (g->stop_reason.signum == 5) {
			if (r_str_startswith (ptr1, "watch")
			    || r_str_startswith (ptr1, "rwatch")
			    || r_str_startswith (ptr1, "awatch")) {
				if (!(ptr2 = strchr (ptr1, ':'))) {
					continue;
				}
				ptr2++;
				if (!isxdigit (*ptr2)) {
					continue;
				}
				g->stop_reason.watchpoint.addr = strtoll (ptr2, NULL, 16);
				g->stop_reason.watchpoint.present = true;
				continue;
			}
			if (r_str_startswith (ptr1, "exec") && !g->stop_reason.exec.present) {
				if (!(ptr2 = strchr (ptr1, ':'))) {
					continue;
				}
				ptr2++;
				if (!(g->stop_reason.exec.path = calloc (strlen (ptr1) / 2, 1))) {
					continue;
				}
				unpack_hex (ptr2, strlen (ptr2), g->stop_reason.exec.path);
				g->stop_reason.exec.present = true;
				continue;
			}
			if (r_str_startswith (ptr1, "fork") && !g->stop_reason.fork.present) {
				if (!(ptr2 = strchr (ptr1, ':'))) {
					continue;
				}
				ptr2++;
				if (read_thread_id (ptr2, &g->stop_reason.fork.pid,
						    &g->stop_reason.fork.tid,
						    g->stub_features.multiprocess) < 0) {
					continue;
				}
				g->stop_reason.fork.present = true;
				continue;
			}
			if (r_str_startswith (ptr1, "vfork") && !g->stop_reason.vfork.present) {
				if (!(ptr2 = strchr (ptr1, ':'))) {
					continue;
				}
				ptr2++;
				if (read_thread_id (ptr2, &g->stop_reason.vfork.pid,
						    &g->stop_reason.vfork.tid,
						    g->stub_features.multiprocess) < 0) {
					continue;
				}
				g->stop_reason.vfork.present = true;
				continue;
			}
			if (r_str_startswith (ptr1, "vforkdone")) {
				g->stop_reason.vforkdone = true;
				continue;
			}
			if (r_str_startswith (ptr1, "library")) {
				g->stop_reason.library = true;
				continue;
			}
			if (r_str_startswith (ptr1, "swbreak")) {
				g->stop_reason.swbreak = true;
				continue;
			}
			if (r_str_startswith (ptr1, "hwbreak")) {
				g->stop_reason.hwbreak = true;
				continue;
			}
			if (r_str_startswith (ptr1, "create")) {
				g->stop_reason.create = true;
				continue;
			}
		}
	}
	if (g->stop_reason.signum == 5) {
		g->stop_reason.reason = R_DEBUG_REASON_BREAKPOINT;
	}
	return 0;
}