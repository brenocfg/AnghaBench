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
struct TYPE_7__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  read_buff; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_1__*) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_packet (TYPE_1__*,int) ; 
 int send_msg (TYPE_1__*,char const*) ; 

int test_command(libgdbr_t *g, const char *command) {
	int ret = -1;

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	if ((ret = send_msg (g, command)) < 0) {
		goto end;
	}
	read_packet (g, false);
	hexdump (g->read_buff, g->data_len, 0);

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}