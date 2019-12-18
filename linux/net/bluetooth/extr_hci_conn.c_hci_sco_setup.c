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
struct hci_conn {int /*<<< orphan*/  handle; int /*<<< orphan*/  hdev; struct hci_conn* link; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_add_sco (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_setup_sync (struct hci_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ lmp_esco_capable (int /*<<< orphan*/ ) ; 

void hci_sco_setup(struct hci_conn *conn, __u8 status)
{
	struct hci_conn *sco = conn->link;

	if (!sco)
		return;

	BT_DBG("hcon %p", conn);

	if (!status) {
		if (lmp_esco_capable(conn->hdev))
			hci_setup_sync(sco, conn->handle);
		else
			hci_add_sco(sco, conn->handle);
	} else {
		hci_connect_cfm(sco, status);
		hci_conn_del(sco);
	}
}