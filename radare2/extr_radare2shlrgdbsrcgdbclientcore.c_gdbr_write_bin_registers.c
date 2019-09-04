#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {int data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ libgdbr_t ;
struct TYPE_8__ {int valid; } ;

/* Variables and functions */
 char* CMD_WRITEREGS ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  handle_G (TYPE_1__*) ; 
 int /*<<< orphan*/  pack_hex (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  read_packet (TYPE_1__*,int) ; 
 TYPE_3__ reg_cache ; 
 scalar_t__ send_msg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int gdbr_write_bin_registers(libgdbr_t *g){
	if (!g) {
		return -1;
	}
	reg_cache.valid = false;
	uint64_t buffer_size = g->data_len * 2 + 8;
	char *command = calloc (buffer_size, sizeof (char));
	if (!command) {
		return -1;
	}
	snprintf (command, buffer_size, "%s", CMD_WRITEREGS);
	pack_hex (g->data, g->data_len, command + 1);
	if (send_msg (g, command) < 0) {
		free (command);
		return -1;
	}
	read_packet (g, false);
	free (command);
	handle_G (g);
	return 0;
}