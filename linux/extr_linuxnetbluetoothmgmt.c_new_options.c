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
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MGMT_OPTION_EVENTS ; 
 int /*<<< orphan*/  MGMT_EV_NEW_CONFIG_OPTIONS ; 
 int /*<<< orphan*/  get_missing_options (struct hci_dev*) ; 
 int mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sock*) ; 

__attribute__((used)) static int new_options(struct hci_dev *hdev, struct sock *skip)
{
	__le32 options = get_missing_options(hdev);

	return mgmt_limited_event(MGMT_EV_NEW_CONFIG_OPTIONS, hdev, &options,
				  sizeof(options), HCI_MGMT_OPTION_EVENTS, skip);
}