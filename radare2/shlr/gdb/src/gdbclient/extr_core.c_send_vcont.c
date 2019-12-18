#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_14__ {int is_valid; } ;
struct TYPE_12__ {int /*<<< orphan*/  r; int /*<<< orphan*/  t; int /*<<< orphan*/  C; int /*<<< orphan*/  c; int /*<<< orphan*/  S; int /*<<< orphan*/  s; } ;
struct TYPE_13__ {TYPE_1__ vcont; int /*<<< orphan*/  vContSupported; } ;
struct TYPE_15__ {int /*<<< orphan*/  sock; TYPE_3__ stop_reason; TYPE_2__ stub_features; } ;
typedef  TYPE_4__ libgdbr_t ;
struct TYPE_16__ {int valid; } ;

/* Variables and functions */
 char* CMD_C ; 
 int _isbreaked ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_4__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_4__*) ; 
 int handle_cont (TYPE_4__*) ; 
 void* r_cons_sleep_begin () ; 
 int /*<<< orphan*/  r_cons_sleep_end (void*) ; 
 scalar_t__ r_socket_is_connected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ ,char*,int) ; 
 int read_packet (TYPE_4__*,int) ; 
 TYPE_7__ reg_cache ; 
 int send_msg (TYPE_4__*,char*) ; 
 int snprintf (char*,int,char*,char const*,...) ; 

int send_vcont(libgdbr_t *g, const char *command, const char *thread_id) {
	char tmp[255] = { 0 };
	int ret = -1;
	void *bed = NULL;

	if (!g) {
		return -1;
	}

	if (!g->stub_features.vContSupported) {
		ret = snprintf (tmp, sizeof (tmp) - 1, "%s", command);
	} else {
		bool supported = false;
		switch (*command) {
		case 's':
			if (g->stub_features.vcont.s) {
				supported = true;
			}
			break;
		case 'S':
			if (g->stub_features.vcont.S) {
				supported = true;
			}
			break;
		case 'c':
			if (g->stub_features.vcont.c) {
				supported = true;
			}
			break;
		case 'C':
			if (g->stub_features.vcont.C) {
				supported = true;
			}
			break;
		case 't':
			if (g->stub_features.vcont.t) {
				supported = true;
			}
			break;
		case 'r':
			if (g->stub_features.vcont.r) {
				supported = true;
			}
			break;
		}
		if (supported) {
			if (!thread_id) {
				ret = snprintf (tmp, sizeof (tmp) - 1, "%s;%s", CMD_C, command);
			} else {
				ret = snprintf (tmp, sizeof (tmp) - 1, "%s;%s:%s", CMD_C, command, thread_id);
			}
		} else {
			ret = snprintf (tmp, sizeof (tmp) - 1, "%s", command);
		}
	}
	if (ret < 0) {
		return ret;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}
	reg_cache.valid = false;
	g->stop_reason.is_valid = false;
	ret = send_msg (g, tmp);
	if (ret < 0) {
		return ret;
	}

	bed = r_cons_sleep_begin ();
	while ((ret = read_packet (g, true)) < 0 && !_isbreaked && r_socket_is_connected (g->sock));
	if (_isbreaked) {
		_isbreaked = false;
		// Stop target
		r_socket_write (g->sock, "\x03", 1);
		// Read the stop reason
		if (read_packet (g, false) < 0) {
			ret = -1;
			goto end;
		}
	}

	ret = handle_cont (g);
end:
	r_cons_sleep_end (bed);
	gdbr_lock_leave (g);
	return ret;
}