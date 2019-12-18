#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbr_lock_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbr_lock_leave (int /*<<< orphan*/ *) ; 
 int handle_stop_reason (int /*<<< orphan*/ *) ; 
 scalar_t__ read_packet (int /*<<< orphan*/ *,int) ; 
 scalar_t__ send_msg (int /*<<< orphan*/ *,char*) ; 

int gdbr_stop_reason(libgdbr_t *g) {
	int ret = -1;
	if (!gdbr_lock_enter (g)) {
		goto end;
	}
	if (!g || send_msg (g, "?") < 0 || read_packet (g, false) < 0) {
		ret = -1;
		goto end;
	}
	ret = handle_stop_reason (g);
end:
	gdbr_lock_leave (g);
	return ret;
}