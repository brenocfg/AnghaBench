#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_13__ {int is_valid; } ;
struct TYPE_11__ {int /*<<< orphan*/  r; int /*<<< orphan*/  t; int /*<<< orphan*/  C; int /*<<< orphan*/  c; int /*<<< orphan*/  S; int /*<<< orphan*/  s; } ;
struct TYPE_12__ {TYPE_1__ vcont; int /*<<< orphan*/  vContSupported; } ;
struct TYPE_14__ {int /*<<< orphan*/  sock; TYPE_3__ stop_reason; TYPE_2__ stub_features; } ;
typedef  TYPE_4__ libgdbr_t ;
struct TYPE_15__ {int valid; } ;

/* Variables and functions */
 char* CMD_C ; 
 int /*<<< orphan*/  SET_SIGINT_HANDLER (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNSET_SIGINT_HANDLER () ; 
 int _isbreaked ; 
 int /*<<< orphan*/  _sigint_handler ; 
 int handle_cont (TYPE_4__*) ; 
 scalar_t__ r_socket_is_connected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ ,char*,int) ; 
 int read_packet (TYPE_4__*,int) ; 
 TYPE_7__ reg_cache ; 
 int send_msg (TYPE_4__*,char*) ; 
 int snprintf (char*,int,char*,char const*,...) ; 

int send_vcont(libgdbr_t *g, const char *command, const char *thread_id) {
	char tmp[255] = {0};
	int ret;
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
	reg_cache.valid = false;
	g->stop_reason.is_valid = false;
	ret = send_msg (g, tmp);
	if (ret < 0) {
		return ret;
	}

	SET_SIGINT_HANDLER (g, _sigint_handler);
	while ((ret = read_packet (g, true)) < 0 && !_isbreaked && r_socket_is_connected (g->sock));
	UNSET_SIGINT_HANDLER ();
	if (_isbreaked) {
		_isbreaked = false;
		// Stop target
		r_socket_write (g->sock, "\x03", 1);
		// Read the stop reason
		if (read_packet (g, false) < 0) {
			return -1;
		}
	}
	return handle_cont (g);
}