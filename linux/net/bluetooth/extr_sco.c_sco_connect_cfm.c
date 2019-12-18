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
struct sco_conn {int dummy; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ESCO_LINK ; 
 scalar_t__ SCO_LINK ; 
 int /*<<< orphan*/  bt_to_errno (int /*<<< orphan*/ ) ; 
 struct sco_conn* sco_conn_add (struct hci_conn*) ; 
 int /*<<< orphan*/  sco_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_conn_ready (struct sco_conn*) ; 

__attribute__((used)) static void sco_connect_cfm(struct hci_conn *hcon, __u8 status)
{
	if (hcon->type != SCO_LINK && hcon->type != ESCO_LINK)
		return;

	BT_DBG("hcon %p bdaddr %pMR status %d", hcon, &hcon->dst, status);

	if (!status) {
		struct sco_conn *conn;

		conn = sco_conn_add(hcon);
		if (conn)
			sco_conn_ready(conn);
	} else
		sco_conn_del(hcon, bt_to_errno(status));
}