#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int quirks; } ;
struct TYPE_4__ {int /*<<< orphan*/  idev; TYPE_1__ config; } ;

/* Variables and functions */
 int FORCE_TABLET_MODE_IF_UNDOCK ; 
 int INVERT_DOCK_STATE_BIT ; 
 int INVERT_TABLET_MODE_BIT ; 
 int /*<<< orphan*/  SW_DOCK ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 TYPE_2__ fujitsu ; 
 int fujitsu_read_register (int) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fujitsu_send_state(void)
{
	int state;
	int dock, tablet_mode;

	state = fujitsu_read_register(0xdd);

	dock = state & 0x02;
	if (fujitsu.config.quirks & INVERT_DOCK_STATE_BIT)
		dock = !dock;

	if ((fujitsu.config.quirks & FORCE_TABLET_MODE_IF_UNDOCK) && (!dock)) {
		tablet_mode = 1;
	} else{
		tablet_mode = state & 0x01;
		if (fujitsu.config.quirks & INVERT_TABLET_MODE_BIT)
			tablet_mode = !tablet_mode;
	}

	input_report_switch(fujitsu.idev, SW_DOCK, dock);
	input_report_switch(fujitsu.idev, SW_TABLET_MODE, tablet_mode);
	input_sync(fujitsu.idev);
}