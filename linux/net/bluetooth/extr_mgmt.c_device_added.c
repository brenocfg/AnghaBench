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
typedef  void* u8 ;
struct sock {int dummy; } ;
struct TYPE_2__ {void* type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_ev_device_added {void* action; TYPE_1__ addr; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_EV_DEVICE_ADDED ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_device_added*,int,struct sock*) ; 

__attribute__((used)) static void device_added(struct sock *sk, struct hci_dev *hdev,
			 bdaddr_t *bdaddr, u8 type, u8 action)
{
	struct mgmt_ev_device_added ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = type;
	ev.action = action;

	mgmt_event(MGMT_EV_DEVICE_ADDED, hdev, &ev, sizeof(ev), sk);
}