#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ multiprocess; } ;
struct TYPE_10__ {int is_valid; } ;
struct TYPE_12__ {scalar_t__ pid; TYPE_2__ stub_features; TYPE_1__ stop_reason; int /*<<< orphan*/  sock; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_13__ {int valid; } ;

/* Variables and functions */
 int gdbr_kill_pid (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_3__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_3__*) ; 
 TYPE_5__ reg_cache ; 
 int send_msg (TYPE_3__*,char*) ; 

int gdbr_kill(libgdbr_t *g) {
	int ret = -1;

	if (!g || !g->sock) {
		return -1;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	reg_cache.valid = false;
	g->stop_reason.is_valid = false;

	if (g->stub_features.multiprocess) {
		if (g->pid <= 0) {
			ret = -1;
			goto end;
		}
		ret = gdbr_kill_pid (g, g->pid);
		goto end;
	}

	if ((ret = send_msg (g, "k")) < 0) {
		goto end;
	}

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}