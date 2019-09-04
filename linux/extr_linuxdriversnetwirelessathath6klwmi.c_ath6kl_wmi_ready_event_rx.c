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
struct wmi_ready_event_2 {int /*<<< orphan*/  phy_cap; int /*<<< orphan*/  abi_version; int /*<<< orphan*/  sw_version; int /*<<< orphan*/  mac_addr; } ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ath6kl_ready_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_ready_event_rx(struct wmi *wmi, u8 *datap, int len)
{
	struct wmi_ready_event_2 *ev = (struct wmi_ready_event_2 *) datap;

	if (len < sizeof(struct wmi_ready_event_2))
		return -EINVAL;

	ath6kl_ready_event(wmi->parent_dev, ev->mac_addr,
			   le32_to_cpu(ev->sw_version),
			   le32_to_cpu(ev->abi_version), ev->phy_cap);

	return 0;
}