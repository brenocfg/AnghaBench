#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int extended_mode; } ;
struct TYPE_10__ {int is_valid; } ;
struct TYPE_12__ {TYPE_2__ stub_features; TYPE_1__ stop_reason; int /*<<< orphan*/  sock; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_13__ {int valid; } ;

/* Variables and functions */
 char* CMD_ATTACH ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gdbr_check_extended_mode (TYPE_3__*) ; 
 int handle_attach (TYPE_3__*) ; 
 scalar_t__ read_packet (TYPE_3__*,int) ; 
 TYPE_5__ reg_cache ; 
 int send_msg (TYPE_3__*,char*) ; 
 int snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 

int gdbr_attach(libgdbr_t *g, int pid) {
	int ret;
	char *cmd;
	size_t buffer_size;

	if (!g || !g->sock) {
		return -1;
	}
	g->stop_reason.is_valid = false;
	reg_cache.valid = false;

	if (g->stub_features.extended_mode == -1) {
		gdbr_check_extended_mode (g);
	}

	if (!g->stub_features.extended_mode) {
		// vAttach needs extended mode to do anything.
		return -2;
	}

	buffer_size = strlen (CMD_ATTACH) + (sizeof (int) * 2) + 1;
	cmd = calloc (buffer_size, sizeof (char));
	if (!cmd) {
		return -1;
	}

	ret = snprintf (cmd, buffer_size, "%s%x", CMD_ATTACH, pid);
	if (ret < 0) {
		free (cmd);
		return ret;
	}

	ret = send_msg (g, cmd);
	free(cmd);
	if (ret < 0) {
		return ret;
	}

	if (read_packet (g, false) >= 0) {
		return handle_attach (g);
	}
	return -1;
}