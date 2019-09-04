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
struct sock {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CHANNEL_CONTROL ; 
 int mgmt_send_event (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,struct sock*) ; 

__attribute__((used)) static int mgmt_limited_event(u16 event, struct hci_dev *hdev, void *data,
			      u16 len, int flag, struct sock *skip_sk)
{
	return mgmt_send_event(event, hdev, HCI_CHANNEL_CONTROL, data, len,
			       flag, skip_sk);
}