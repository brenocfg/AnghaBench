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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_channel_list_reply {int dummy; } ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ath6kl_wakeup_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_ch_list_reply_rx(struct wmi *wmi, u8 *datap, int len)
{
	if (len < sizeof(struct wmi_channel_list_reply))
		return -EINVAL;

	ath6kl_wakeup_event(wmi->parent_dev);

	return 0;
}