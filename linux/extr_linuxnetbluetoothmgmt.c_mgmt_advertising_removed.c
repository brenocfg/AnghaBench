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
struct sock {int dummy; } ;
struct mgmt_ev_advertising_removed {int /*<<< orphan*/  instance; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_EV_ADVERTISING_REMOVED ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_advertising_removed*,int,struct sock*) ; 

void mgmt_advertising_removed(struct sock *sk, struct hci_dev *hdev,
			      u8 instance)
{
	struct mgmt_ev_advertising_removed ev;

	ev.instance = instance;

	mgmt_event(MGMT_EV_ADVERTISING_REMOVED, hdev, &ev, sizeof(ev), sk);
}