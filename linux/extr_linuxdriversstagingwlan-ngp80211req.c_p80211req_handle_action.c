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
typedef  int u32 ;
struct wlandevice {int hostwep; } ;

/* Variables and functions */
 int P80211ENUM_truth_false ; 
 int P80211ENUM_truth_true ; 

__attribute__((used)) static void p80211req_handle_action(struct wlandevice *wlandev, u32 *data,
				    int isget, u32 flag)
{
	if (isget) {
		if (wlandev->hostwep & flag)
			*data = P80211ENUM_truth_true;
		else
			*data = P80211ENUM_truth_false;
	} else {
		wlandev->hostwep &= ~flag;
		if (*data == P80211ENUM_truth_true)
			wlandev->hostwep |= flag;
	}
}