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
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MGMT_SETTING_EVENTS ; 
 int /*<<< orphan*/  MGMT_EV_NEW_SETTINGS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_settings (struct hci_dev*) ; 
 int mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sock*) ; 

__attribute__((used)) static int new_settings(struct hci_dev *hdev, struct sock *skip)
{
	__le32 ev = cpu_to_le32(get_current_settings(hdev));

	return mgmt_limited_event(MGMT_EV_NEW_SETTINGS, hdev, &ev,
				  sizeof(ev), HCI_MGMT_SETTING_EVENTS, skip);
}