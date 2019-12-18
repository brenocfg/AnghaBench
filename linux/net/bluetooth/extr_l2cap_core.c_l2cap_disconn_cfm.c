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
struct hci_conn {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  bt_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_disconn_cfm(struct hci_conn *hcon, u8 reason)
{
	if (hcon->type != ACL_LINK && hcon->type != LE_LINK)
		return;

	BT_DBG("hcon %p reason %d", hcon, reason);

	l2cap_conn_del(hcon, bt_to_errno(reason));
}