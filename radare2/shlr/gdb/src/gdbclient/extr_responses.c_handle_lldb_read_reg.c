#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* read_buff; size_t data_len; int /*<<< orphan*/ * data; TYPE_1__* registers; } ;
typedef  TYPE_2__ libgdbr_t ;
struct TYPE_5__ {size_t offset; size_t size; scalar_t__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ send_ack (TYPE_2__*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unpack_hex (char*,int /*<<< orphan*/ ,char*) ; 

int handle_lldb_read_reg(libgdbr_t *g) {
	if (send_ack (g) < 0) {
		return -1;
	}
	char *ptr, *ptr2, *buf;
	size_t regnum, tot_regs, buflen = 0;

	// Get maximum register number
	for (regnum = 0; *g->registers[regnum].name; regnum++) {
		if (g->registers[regnum].offset + g->registers[regnum].size > buflen) {
			buflen = g->registers[regnum].offset + g->registers[regnum].size;
		}
	}
	tot_regs = regnum;

	// We're not using the receive buffer till next packet anyway. Better use it
	buf = g->read_buff;
	memset (buf, 0, buflen);

	if (!(ptr = strtok (g->data, ";"))) {
		return -1;
	}
	while (ptr) {
		if (!isxdigit (*ptr)) {
			// This is not a reg value. Skip
			ptr = strtok (NULL, ";");
			continue;
		}
		// Get register number
		regnum = (int) strtoul (ptr, NULL, 16);
		if (regnum >= tot_regs || !(ptr2 = strchr (ptr, ':'))) {
			ptr = strtok (NULL, ";");
			continue;
		}
		ptr2++;
		// Write to offset
		unpack_hex (ptr2, strlen (ptr2), buf + g->registers[regnum].offset);
		ptr = strtok (NULL, ";");
		continue;
	}
	memcpy (g->data, buf, buflen);
	g->data_len = buflen;
	return 0;
}