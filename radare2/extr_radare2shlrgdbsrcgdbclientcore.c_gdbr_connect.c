#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_16__ {int pkt_sz; int qC; scalar_t__ qXfer_features_read; scalar_t__ QStartNoAckMode; } ;
struct TYPE_17__ {int connected; int no_ack; scalar_t__ remote_type; TYPE_1__ stub_features; int /*<<< orphan*/  data; scalar_t__ pid; scalar_t__ tid; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ libgdbr_t ;
struct TYPE_18__ {char* buf; } ;
typedef  TYPE_3__ RStrBuf ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_MAX_PKTSZ ; 
 scalar_t__ GDB_REMOTE_TYPE_LLDB ; 
 void* R_MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ R_MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  gdbr_check_vcont (TYPE_2__*) ; 
 int gdbr_connect_lldb (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_read_target_xml (TYPE_2__*) ; 
 scalar_t__ gdbr_select (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int handle_qC (TYPE_2__*) ; 
 int handle_qSupported (TYPE_2__*) ; 
 int r_socket_connect_serial (int /*<<< orphan*/ ,char const*,int,int) ; 
 int r_socket_connect_tcp (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  r_strbuf_init (TYPE_3__*) ; 
 char* r_sys_getenv (char*) ; 
 int /*<<< orphan*/  read_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reg_cache_init (TYPE_2__*) ; 
 int send_ack (TYPE_2__*) ; 
 int send_msg (TYPE_2__*,char const*) ; 
 int snprintf (char*,int,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

int gdbr_connect(libgdbr_t *g, const char *host, int port) {
	const char *message = "qSupported:multiprocess+;qRelocInsn+;xmlRegisters=i386";
	RStrBuf tmp;
	r_strbuf_init (&tmp);
	int ret;
	if (!g || !host) {
		return -1;
	}
	// Initial max_packet_size for remote target (minimum so far for AVR = 64)
	g->stub_features.pkt_sz = 64;
	char *env_pktsz_str;
	ut32 env_pktsz = 0;
	if ((env_pktsz_str = r_sys_getenv ("R2_GDB_PKTSZ"))) {
		if ((env_pktsz = (ut32) strtoul (env_pktsz_str, NULL, 10))) {
			g->stub_features.pkt_sz = R_MAX (env_pktsz, GDB_MAX_PKTSZ);
		}
	}
	ret = snprintf (tmp.buf, sizeof (tmp.buf) - 1, "%d", port);
	if (!ret) {
		return -1;
	}
	if (*host == '/') {
		ret = r_socket_connect_serial (g->sock, host, port, 1);
	} else {
		ret = r_socket_connect_tcp (g->sock, host, tmp.buf, 400);
	}
	if (!ret) {
		return -1;
	}
	if (send_ack (g) < 0) {
		return -1;
	}
	read_packet (g, true); // vcont=true lets us skip if we get no reply
	g->connected = 1;
	// TODO add config possibility here
	ret = send_msg (g, message);
	if (ret < 0) {
		return ret;
	}
	read_packet (g, false);
	ret = handle_qSupported (g);
	if (ret < 0) {
		return ret;
	}
	if (env_pktsz > 0) {
		g->stub_features.pkt_sz = R_MAX (R_MIN (env_pktsz, g->stub_features.pkt_sz), GDB_MAX_PKTSZ);
	}
	// If no-ack supported, enable no-ack mode (should speed up things)
	if (g->stub_features.QStartNoAckMode) {
		if (send_msg (g, "QStartNoAckMode") < 0) {
			return -1;
		}
		read_packet (g, false);
		if (!strncmp (g->data, "OK", 2)) {
			// Just in case, send ack
			send_ack (g);
			g->no_ack = true;
		}
	}
	if (g->remote_type == GDB_REMOTE_TYPE_LLDB) {
		return gdbr_connect_lldb (g);
	}
	// Query the thread / process id
	g->stub_features.qC = true;
	g->pid = g->tid = 0;
	ret = send_msg (g, "qC");
	if (ret < 0) {
		return ret;
	}
	read_packet (g, false);
	ret = handle_qC (g);
	if (ret < 0) {
		g->stub_features.qC = false;
	}
	// Check if vCont is supported
	gdbr_check_vcont (g);
	// Set pid/thread for operations other than "step" and "continue"
	if (gdbr_select (g, g->pid, 0) < 0) {
		// return -1;
	}
	// Set thread for "step" and "continue" operations
	snprintf (tmp.buf, sizeof (tmp.buf) - 1, "Hc-1");
	ret = send_msg (g, tmp.buf);
	if (ret < 0) {
		return ret;
	}
	read_packet (g, false);
	ret = send_ack (g);
	if (ret < 0) {
		return ret;
	}
	if (strcmp (g->data, "OK")) {
		// return -1;
	}
	if (g->stub_features.qXfer_features_read) {
		gdbr_read_target_xml (g);
	}
	reg_cache_init (g);
	return ret;
}