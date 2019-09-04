#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* data; size_t data_len; } ;
typedef  TYPE_1__ libgdbr_t ;
typedef  int /*<<< orphan*/  (* gdbr_server_cmd_cb ) (TYPE_1__*,void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 scalar_t__ send_ack (TYPE_1__*) ; 
 int send_msg (TYPE_1__*,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int _server_handle_vCont(libgdbr_t *g, gdbr_server_cmd_cb cmd_cb, void *core_ptr) {
	char *action = NULL;
	if (send_ack (g) < 0) {
		return -1;
	}
	g->data[g->data_len] = '\0';
	if (g->data[5] == '?') {
		// Query about everything we support
		return send_msg (g, "vCont;c;s");
	}
	if (!(action = strtok (g->data, ";"))) {
		return send_msg (g, "E01");
	}
	while ((action = strtok (NULL, ";"))) {
		eprintf ("action: %s\n", action);
		switch (action[0]) {
		case 's':
			// TODO handle thread selections
			if (cmd_cb (g, core_ptr, "ds", NULL, 0) < 0) {
				send_msg (g, "E01");
				return -1;
			}
			return send_msg (g, "OK");
		case 'c':
			// TODO handle thread selections
			if (cmd_cb (g, core_ptr, "dc", NULL, 0) < 0) {
				send_msg (g, "E01");
				return -1;
			}
			return send_msg (g, "OK");
		default:
			// TODO support others
			return send_msg (g, "E01");
		}
	}
	return -1;
}