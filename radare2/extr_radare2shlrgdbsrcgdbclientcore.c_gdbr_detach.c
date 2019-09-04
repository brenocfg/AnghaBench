#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_valid; } ;
struct TYPE_8__ {TYPE_1__ stop_reason; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ libgdbr_t ;
struct TYPE_9__ {int valid; } ;

/* Variables and functions */
 int gdbr_disconnect (TYPE_2__*) ; 
 TYPE_4__ reg_cache ; 
 int send_msg (TYPE_2__*,char*) ; 

int gdbr_detach(libgdbr_t *g) {
	int ret;

	if (!g || !g->sock) {
		return -1;
	}
	reg_cache.valid = false;
	g->stop_reason.is_valid = false;
	ret = send_msg (g, "D");
	if (ret < 0) {
		return -1;
	}
	// Disconnect
	return gdbr_disconnect (g);
}