#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  gport; } ;
typedef  TYPE_1__ RIOGprobe ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  gprobe_debugoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gprobe_debugon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gprobe_getdeviceid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gprobe_getinformation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gprobe_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gprobe_runcode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ r_str_startswith (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *__system (RIO *io, RIODesc *fd, const char *cmd) {
	RIOGprobe *gprobe;

	if (!fd || !fd->data) {
		return NULL;
	}
	gprobe = (RIOGprobe *)fd->data;

	if (!cmd[0] || cmd[0] == '?' || !strcmp (cmd, "help")) {
		printf ("Usage: =!cmd args\n"
			" =!reset code\n"
			" =!debugon\n"
			" =!debugoff\n"
			" =!runcode address\n"
			" =!getdeviceid\n"
			" =!getinformation\n");
		return NULL;
	}

	if (r_str_startswith (cmd, "reset") && (strlen (cmd) > 6)) {
		ut32 code = (ut32)strtoul (cmd + 6, NULL, 10);

		gprobe_reset (&gprobe->gport, code);

		return NULL;
	}

	if (r_str_startswith (cmd, "debugon")) {
		gprobe_debugon (&gprobe->gport);

		return NULL;
	}

	if (r_str_startswith (cmd, "debugoff")) {
		gprobe_debugoff (&gprobe->gport);

		return NULL;
	}

	if (r_str_startswith (cmd, "runcode") && (strlen (cmd) > 8)) {
		ut32 address = (ut32)strtoul (cmd + 8, NULL, 0);

		gprobe_runcode (&gprobe->gport, address);

		return NULL;
	}

	if (r_str_startswith (cmd, "getdeviceid")) {
		ut8 index = 0;

		while (!gprobe_getdeviceid (&gprobe->gport, index++)) {
		};

		return NULL;
	}

	if (r_str_startswith (cmd, "getinformation")) {
		gprobe_getinformation (&gprobe->gport);

		return NULL;
	}

	printf ("Try: '=!?'\n");

	return NULL;
}