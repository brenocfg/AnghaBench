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
struct sock {int dummy; } ;
struct mgmt_ev_phy_configuration_changed {int /*<<< orphan*/  selected_phys; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_EV_PHY_CONFIGURATION_CHANGED ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_selected_phys (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct mgmt_ev_phy_configuration_changed*,int /*<<< orphan*/ ,int) ; 
 int mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_phy_configuration_changed*,int,struct sock*) ; 

int mgmt_phy_configuration_changed(struct hci_dev *hdev, struct sock *skip)
{
	struct mgmt_ev_phy_configuration_changed ev;

	memset(&ev, 0, sizeof(ev));

	ev.selected_phys = cpu_to_le32(get_selected_phys(hdev));

	return mgmt_event(MGMT_EV_PHY_CONFIGURATION_CHANGED, hdev, &ev,
			  sizeof(ev), skip);
}