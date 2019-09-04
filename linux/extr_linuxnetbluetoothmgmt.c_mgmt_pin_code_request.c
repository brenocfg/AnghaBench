#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_ev_pin_code_request {int /*<<< orphan*/  secure; TYPE_1__ addr; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  MGMT_EV_PIN_CODE_REQUEST ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_pin_code_request*,int,int /*<<< orphan*/ *) ; 

void mgmt_pin_code_request(struct hci_dev *hdev, bdaddr_t *bdaddr, u8 secure)
{
	struct mgmt_ev_pin_code_request ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = BDADDR_BREDR;
	ev.secure = secure;

	mgmt_event(MGMT_EV_PIN_CODE_REQUEST, hdev, &ev, sizeof(ev), NULL);
}