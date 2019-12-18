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
struct input_handle {int dummy; } ;

/* Variables and functions */
 unsigned int EV_KEY ; 
 unsigned int EV_SW ; 
#define  KEY_BLUETOOTH 132 
#define  KEY_RFKILL 131 
#define  KEY_UWB 130 
#define  KEY_WIMAX 129 
#define  KEY_WLAN 128 
 int /*<<< orphan*/  RFKILL_TYPE_ALL ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_UWB ; 
 int /*<<< orphan*/  RFKILL_TYPE_WIMAX ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 unsigned int SW_RFKILL_ALL ; 
 int /*<<< orphan*/  rfkill_schedule_evsw_rfkillall (int) ; 
 int /*<<< orphan*/  rfkill_schedule_toggle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfkill_event(struct input_handle *handle, unsigned int type,
			unsigned int code, int data)
{
	if (type == EV_KEY && data == 1) {
		switch (code) {
		case KEY_WLAN:
			rfkill_schedule_toggle(RFKILL_TYPE_WLAN);
			break;
		case KEY_BLUETOOTH:
			rfkill_schedule_toggle(RFKILL_TYPE_BLUETOOTH);
			break;
		case KEY_UWB:
			rfkill_schedule_toggle(RFKILL_TYPE_UWB);
			break;
		case KEY_WIMAX:
			rfkill_schedule_toggle(RFKILL_TYPE_WIMAX);
			break;
		case KEY_RFKILL:
			rfkill_schedule_toggle(RFKILL_TYPE_ALL);
			break;
		}
	} else if (type == EV_SW && code == SW_RFKILL_ALL)
		rfkill_schedule_evsw_rfkillall(data);
}