#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {int data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ libgdbr_t ;
struct TYPE_10__ {int valid; } ;

/* Variables and functions */
 char* CMD_WRITEREGS ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_G (TYPE_1__*) ; 
 int /*<<< orphan*/  pack_hex (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ read_packet (TYPE_1__*,int) ; 
 TYPE_3__ reg_cache ; 
 scalar_t__ send_msg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int gdbr_write_bin_registers(libgdbr_t *g){
	int ret = -1;
	uint64_t buffer_size;
	char *command = NULL;

	if (!g) {
		return -1;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	buffer_size = g->data_len * 2 + 8;
	reg_cache.valid = false;

	command = calloc (buffer_size, sizeof (char));
	if (!command) {
		ret = -1;
		goto end;
	}
	snprintf (command, buffer_size, "%s", CMD_WRITEREGS);
	pack_hex (g->data, g->data_len, command + 1);
	if (send_msg (g, command) < 0) {
		ret = -1;
		goto end;
	}
	if (read_packet (g, false) >= 0) {
		handle_G (g);
	} else {
		ret = -1;
		goto end;
	}

	ret = 0;
end:
	gdbr_lock_leave (g);
	if (command) {
		free (command);
	}
	return ret;
}