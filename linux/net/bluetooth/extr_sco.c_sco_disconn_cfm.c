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
struct hci_conn {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESCO_LINK ; 
 scalar_t__ SCO_LINK ; 
 int /*<<< orphan*/  bt_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sco_disconn_cfm(struct hci_conn *hcon, __u8 reason)
{
	if (hcon->type != SCO_LINK && hcon->type != ESCO_LINK)
		return;

	BT_DBG("hcon %p reason %d", hcon, reason);

	sco_conn_del(hcon, bt_to_errno(reason));
}