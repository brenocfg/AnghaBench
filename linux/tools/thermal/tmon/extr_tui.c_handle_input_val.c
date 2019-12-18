#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_6__ {int t_target; } ;
struct TYPE_5__ {int nr_cooling_dev; TYPE_1__* cdi; } ;
struct TYPE_4__ {int /*<<< orphan*/  instance; } ;
typedef  int /*<<< orphan*/  PANEL ;

/* Variables and functions */
 char* CDEV ; 
 int MAX_CTRL_TEMP ; 
 int MIN_CTRL_TEMP ; 
 char* THERMAL_SYSFS ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 scalar_t__ dialogue_on ; 
 int /*<<< orphan*/ * dialogue_window ; 
 int /*<<< orphan*/  echo () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 TYPE_3__ p_param ; 
 scalar_t__ panel_userptr (int /*<<< orphan*/ *) ; 
 TYPE_2__ ptdata ; 
 int /*<<< orphan*/  show_control_w () ; 
 int /*<<< orphan*/  show_data_w () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sysfs_set_ulong (char*,char*,int) ; 
 int /*<<< orphan*/ * top ; 
 int /*<<< orphan*/  top_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wgetnstr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  write_status_bar (int,char*) ; 

__attribute__((used)) static void handle_input_val(int ch)
{
	char buf[32];
	int val;
	char path[256];
	WINDOW *w = dialogue_window;

	echo();
	keypad(w, TRUE);
	wgetnstr(w, buf, 31);
	val = atoi(buf);

	if (ch == ptdata.nr_cooling_dev) {
		snprintf(buf, 31, "Invalid Temp %d! %d-%d", val,
			MIN_CTRL_TEMP, MAX_CTRL_TEMP);
		if (val < MIN_CTRL_TEMP || val > MAX_CTRL_TEMP)
			write_status_bar(40, buf);
		else {
			p_param.t_target = val;
			snprintf(buf, 31, "Set New Target Temp %d", val);
			write_status_bar(40, buf);
		}
	} else {
		snprintf(path, 256, "%s/%s%d", THERMAL_SYSFS,
			CDEV, ptdata.cdi[ch].instance);
		sysfs_set_ulong(path, "cur_state", val);
	}
	noecho();
	dialogue_on = 0;
	show_data_w();
	show_control_w();

	top = (PANEL *)panel_userptr(top);
	top_panel(top);
}