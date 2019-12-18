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
typedef  int /*<<< orphan*/  u16 ;
struct mgmt_pending_cmd {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CHANNEL_CONTROL ; 
 struct mgmt_pending_cmd* mgmt_pending_find_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hci_dev*,void const*) ; 

__attribute__((used)) static struct mgmt_pending_cmd *pending_find_data(u16 opcode,
						  struct hci_dev *hdev,
						  const void *data)
{
	return mgmt_pending_find_data(HCI_CHANNEL_CONTROL, opcode, hdev, data);
}