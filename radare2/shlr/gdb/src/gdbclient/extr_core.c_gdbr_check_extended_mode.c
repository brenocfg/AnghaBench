#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int extended_mode; } ;
struct TYPE_11__ {int is_valid; } ;
struct TYPE_13__ {TYPE_2__ stub_features; int /*<<< orphan*/  data; TYPE_1__ stop_reason; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_14__ {int valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_3__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_3__*) ; 
 int /*<<< orphan*/  read_packet (TYPE_3__*,int) ; 
 TYPE_6__ reg_cache ; 
 int send_ack (TYPE_3__*) ; 
 int send_msg (TYPE_3__*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int gdbr_check_extended_mode(libgdbr_t *g) {
	int ret = -1;

	if (!gdbr_lock_enter (g)) {
		goto end;
	}
	g->stop_reason.is_valid = false;
	reg_cache.valid = false;
	// Activate extended mode if possible.
	ret = send_msg (g, "!");
	if (ret < 0) {
		g->stub_features.extended_mode = 0;
		goto end;
	}
	read_packet (g, false);
	ret = send_ack (g);
	if (ret < 0) {
		g->stub_features.extended_mode = 0;
		goto end;
	}
	if (strncmp (g->data, "OK", 2)) {
		g->stub_features.extended_mode = 0;
		ret = -1;
		goto end;
	}
	g->stub_features.extended_mode = 1;

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}