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
typedef  scalar_t__ u8 ;
struct l2cap_conn {struct l2cap_chan* smp; struct hci_conn* hcon; } ;
struct l2cap_chan {scalar_t__ data; } ;
struct hci_conn {int dummy; } ;
typedef  int /*<<< orphan*/  reason ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ERROR_AUTH_FAILURE ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_FAIL ; 
 int /*<<< orphan*/  mgmt_auth_failed (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_chan_destroy (struct l2cap_conn*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static void smp_failure(struct l2cap_conn *conn, u8 reason)
{
	struct hci_conn *hcon = conn->hcon;
	struct l2cap_chan *chan = conn->smp;

	if (reason)
		smp_send_cmd(conn, SMP_CMD_PAIRING_FAIL, sizeof(reason),
			     &reason);

	mgmt_auth_failed(hcon, HCI_ERROR_AUTH_FAILURE);

	if (chan->data)
		smp_chan_destroy(conn);
}