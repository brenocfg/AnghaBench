#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int extended_mode; } ;
struct TYPE_10__ {int is_valid; } ;
struct TYPE_11__ {TYPE_1__ stub_features; int /*<<< orphan*/  data; TYPE_2__ stop_reason; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_12__ {int valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_packet (TYPE_3__*,int) ; 
 TYPE_6__ reg_cache ; 
 int send_ack (TYPE_3__*) ; 
 int send_msg (TYPE_3__*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int gdbr_check_extended_mode(libgdbr_t *g) {
	int ret;
	g->stop_reason.is_valid = false;
	reg_cache.valid = false;
	// Activate extended mode if possible.
	ret = send_msg (g, "!");
	if (ret < 0) {
		g->stub_features.extended_mode = 0;
		return ret;
	}
	read_packet (g, false);
	ret = send_ack (g);
	if (ret < 0) {
		g->stub_features.extended_mode = 0;
		return ret;
	}
	if (strncmp (g->data, "OK", 2)) {
		g->stub_features.extended_mode = 0;
		return -1;
	}

	g->stub_features.extended_mode = 1;
	return 0;
}