#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ multiprocess; } ;
struct TYPE_8__ {int is_valid; } ;
struct TYPE_10__ {scalar_t__ pid; TYPE_2__ stub_features; TYPE_1__ stop_reason; int /*<<< orphan*/  sock; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_11__ {int valid; } ;

/* Variables and functions */
 int gdbr_kill_pid (TYPE_3__*,scalar_t__) ; 
 TYPE_5__ reg_cache ; 
 int send_msg (TYPE_3__*,char*) ; 

bool gdbr_kill(libgdbr_t *g) {
	int ret;
	if (!g || !g->sock) {
		return false;
	}
	reg_cache.valid = false;
	g->stop_reason.is_valid = false;

	if (g->stub_features.multiprocess) {
		if (g->pid <= 0) {
			return false;
		}
		return gdbr_kill_pid (g, g->pid);
	}

	ret = send_msg (g, "k");
	if (ret < 0) {
		return false;
	}
	return true;
}