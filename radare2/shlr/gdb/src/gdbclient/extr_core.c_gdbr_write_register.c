#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libgdbr_t ;
typedef  int /*<<< orphan*/  command ;
struct TYPE_2__ {int valid; } ;

/* Variables and functions */
 char* CMD_WRITEREG ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  gdbr_lock_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbr_lock_leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pack_hex (char*,int,char*) ; 
 scalar_t__ read_packet (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ reg_cache ; 
 scalar_t__ send_msg (int /*<<< orphan*/ *,char*) ; 
 int snprintf (char*,int,char*,char*,int) ; 

int gdbr_write_register(libgdbr_t *g, int index, char *value, int len) {
	int ret = -1;
	char command[255] = { 0 };
	if (!g) {
		return -1;
	}
	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	reg_cache.valid = false;
	ret = snprintf (command, sizeof (command) - 1, "%s%x=", CMD_WRITEREG, index);
	if (len + ret >= sizeof (command)) {
		eprintf ("command is too small\n");
		ret = -1;
		goto end;
	}
	memcpy (command + ret, value, len);
	pack_hex (value, len, (command + ret));
	if (send_msg (g, command) < 0) {
		ret = -1;
		goto end;
	}
	if (read_packet (g, false) >= 0) {
		handle_P (g);
	}

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}