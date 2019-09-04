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
struct TYPE_7__ {char* data; int pid; } ;
typedef  TYPE_1__ libgdbr_t ;
typedef  scalar_t__ (* gdbr_server_cmd_cb ) (TYPE_1__*,void*,char*,char*,size_t) ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ send_ack (TYPE_1__*) ; 
 int send_msg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int _server_handle_exec_file_read(libgdbr_t *g, gdbr_server_cmd_cb cb,
					 void *core_ptr) {
	char *buf, *ptr, cmd[64] = { 0 };
	size_t buflen = 512;
	int ret;
	if (send_ack (g) < 0) {
		return -1;
	}
	ptr = g->data + strlen ("qXfer:exec-file:read:");
	if (*ptr != ':') {
		int pid;
		if ((pid = (int) strtol (ptr, NULL, 16)) <= 0 || pid != g->pid) {
			return send_msg (g, "E00");
		}
	}
	if (!(ptr = strchr (ptr, ':'))) {
		return send_msg (g, "E00");
	}
	ptr++;
	snprintf (cmd, sizeof (cmd) - 1, "if%s", ptr);
	if (!(buf = malloc (buflen))) {
		send_msg (g, "E01");
		return -1;
	}
	if (cb (g, core_ptr, cmd, buf, buflen) < 0) {
		free (buf);
		return send_msg (g, "E01");
	}
	ret = send_msg (g, buf);
	free (buf);
	return ret;
}