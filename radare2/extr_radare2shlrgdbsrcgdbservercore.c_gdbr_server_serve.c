#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int data_len; char* data; int no_ack; scalar_t__ server_debug; } ;
typedef  TYPE_1__ libgdbr_t ;
typedef  int /*<<< orphan*/  gdbr_server_cmd_cb ;

/* Variables and functions */
 int _server_handle_Hc (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_Hg (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_M (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_P (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_c (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_exec_file_read (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_g (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_k (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_m (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_p (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qAttached (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qC (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qOffsets (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qSupported (TYPE_1__*) ; 
 int _server_handle_qTStatus (TYPE_1__*) ; 
 int _server_handle_qTfV (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qfThreadInfo (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_qsThreadInfo (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_ques (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_s (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_vCont (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_vKill (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int _server_handle_vMustReplyEmpty (TYPE_1__*) ; 
 int _server_handle_z (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 scalar_t__ read_packet (TYPE_1__*,int) ; 
 scalar_t__ send_ack (TYPE_1__*) ; 
 scalar_t__ send_msg (TYPE_1__*,char*) ; 

int gdbr_server_serve(libgdbr_t *g, gdbr_server_cmd_cb cmd_cb, void *core_ptr) {
	int ret;
	if (!g) {
		return -1;
	}
	while (1) {
		if (read_packet (g, false) < 0) {
			continue;
		}
		if (g->data_len == 0) {
			continue;
		}
		if (r_str_startswith (g->data, "k")) {
			return _server_handle_k (g, cmd_cb, core_ptr);
		}
		if (r_str_startswith (g->data, "vKill")) {
			return _server_handle_vKill (g, cmd_cb, core_ptr);
		}
		if (r_str_startswith (g->data, "qSupported")) {
			if ((ret = _server_handle_qSupported (g)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qTStatus")) {
			if ((ret = _server_handle_qTStatus (g)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qC") && g->data_len == 2) {
			if ((ret = _server_handle_qC (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qAttached")) {
			if ((ret = _server_handle_qAttached (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "vMustReplyEmpty")) {
			if ((ret = _server_handle_vMustReplyEmpty (g)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qTfV")) {
			if ((ret = _server_handle_qTfV (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qfThreadInfo")) {
			if ((ret = _server_handle_qfThreadInfo (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qsThreadInfo")) {
			if ((ret = _server_handle_qsThreadInfo (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "Hg")) {
			if ((ret = _server_handle_Hg (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "Hc")) {
			if ((ret = _server_handle_Hc (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "?")) {
			if ((ret = _server_handle_ques (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "g") && g->data_len == 1) {
			if ((ret = _server_handle_g (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "vCont")) {
			if ((ret = _server_handle_vCont (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qOffsets")) {
			if ((ret = _server_handle_qOffsets (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (g->data[0] == 'z' || g->data[0] == 'Z') {
			if ((ret = _server_handle_z (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (g->data[0] == 's') {
			if ((ret = _server_handle_s (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (g->data[0] == 'c') {
			if ((ret = _server_handle_c (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "m")) {
			if ((ret = _server_handle_m (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "M")) {
			if ((ret = _server_handle_M (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "P")) {
			if ((ret = _server_handle_P (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "p")) {
			if ((ret = _server_handle_p (g, cmd_cb, core_ptr)) < 0) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "qXfer:exec-file:read:")) {
			if ((ret = _server_handle_exec_file_read (g, cmd_cb, core_ptr)) < 0 ) {
				return ret;
			}
			continue;
		}
		if (r_str_startswith (g->data, "QStartNoAckMode")) {
			if (send_ack (g) < 0) {
				return -1;
			}
			g->no_ack = true;
			if (g->server_debug) {
				eprintf ("[noack mode enabled]\n");
			}
			if (send_msg (g, "OK") < 0) {
				return -1;
			}
			continue;
		}
		// Unrecognized packet
		if (send_ack (g) < 0 || send_msg (g, "") < 0) {
			g->data[g->data_len] = '\0';
			eprintf ("Unknown packet: %s\n", g->data);
			return -1;
		}
	};
	return ret;
}