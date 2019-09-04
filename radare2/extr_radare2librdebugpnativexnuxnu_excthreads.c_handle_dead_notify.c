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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int msgh_id; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ exc_msg ;
struct TYPE_8__ {int pid; } ;
typedef  TYPE_3__ RDebug ;

/* Variables and functions */

__attribute__((used)) static bool handle_dead_notify (RDebug *dbg, exc_msg *msg) {
	if (msg->hdr.msgh_id == 0x48) {
		dbg->pid = -1;
		return true;
	}
	return false;
}