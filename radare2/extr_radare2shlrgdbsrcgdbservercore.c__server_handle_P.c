#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; TYPE_1__* registers; } ;
typedef  TYPE_2__ libgdbr_t ;
typedef  scalar_t__ (* gdbr_server_cmd_cb ) (TYPE_2__*,void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 scalar_t__ send_ack (TYPE_2__*) ; 
 int send_msg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int _server_handle_P(libgdbr_t *g, gdbr_server_cmd_cb cmd_cb, void *core_ptr) {
	char *ptr, *cmd;
	int regnum, len, i;
	if (send_ack (g) < 0) {
		return -1;
	}
	if (!isxdigit (g->data[1]) || !(ptr = strchr (g->data, '='))) {
		return send_msg (g, "E01");
	}
	ptr++;
	if (!isxdigit (*ptr)) {
		return send_msg (g, "E01");
	}
	regnum = strtol (g->data + 1, NULL, 16);
	// We need to do this because length of register set is not known
	for (i = 0; i < regnum; i++) {
		if (!*g->registers[i].name) {
			return send_msg (g, "E01");
		}
	}
	len = strlen (g->registers[regnum].name) + strlen (ptr) + 10;
	if (!(cmd = calloc (len, sizeof (char)))) {
		return send_msg (g, "E01");
	}
	snprintf (cmd, len - 1, "dr %s=0x%s", g->registers[regnum].name, ptr);
	if (cmd_cb (g, core_ptr, cmd, NULL, 0) < 0) {
		free (cmd);
		send_msg (g, "E01");
		return -1;
	}
	free (cmd);
	return send_msg (g, "OK");
}