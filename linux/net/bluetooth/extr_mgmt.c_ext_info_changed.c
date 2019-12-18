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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct mgmt_ev_ext_info_changed {int /*<<< orphan*/  eir_len; int /*<<< orphan*/  eir; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MGMT_EXT_INFO_EVENTS ; 
 int /*<<< orphan*/  MGMT_EV_EXT_INFO_CHANGED ; 
 scalar_t__ append_eir_data_to_buf (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_ext_info_changed*,scalar_t__,int /*<<< orphan*/ ,struct sock*) ; 

__attribute__((used)) static int ext_info_changed(struct hci_dev *hdev, struct sock *skip)
{
	char buf[512];
	struct mgmt_ev_ext_info_changed *ev = (void *)buf;
	u16 eir_len;

	memset(buf, 0, sizeof(buf));

	eir_len = append_eir_data_to_buf(hdev, ev->eir);
	ev->eir_len = cpu_to_le16(eir_len);

	return mgmt_limited_event(MGMT_EV_EXT_INFO_CHANGED, hdev, ev,
				  sizeof(*ev) + eir_len,
				  HCI_MGMT_EXT_INFO_EVENTS, skip);
}