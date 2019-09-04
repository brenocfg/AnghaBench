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
struct wlandevice {int dummy; } ;
struct p80211msg_dot11req_mibset {int dummy; } ;
struct mibrec {int dummy; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int prism2mib_flag (struct mibrec*,int,struct wlandevice*,struct hfa384x*,struct p80211msg_dot11req_mibset*,void*) ; 

__attribute__((used)) static int prism2mib_excludeunencrypted(struct mibrec *mib,
					int isget,
					struct wlandevice *wlandev,
					struct hfa384x *hw,
					struct p80211msg_dot11req_mibset *msg,
					void *data)
{
	return prism2mib_flag(mib, isget, wlandev, hw, msg, data);
}