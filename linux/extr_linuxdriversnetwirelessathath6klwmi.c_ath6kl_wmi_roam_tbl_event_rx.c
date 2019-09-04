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
struct wmi {int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int ath6kl_debug_roam_tbl_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath6kl_wmi_roam_tbl_event_rx(struct wmi *wmi, u8 *datap, int len)
{
	return ath6kl_debug_roam_tbl_event(wmi->parent_dev, datap, len);
}