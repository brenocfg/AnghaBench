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
struct smp_irk {int /*<<< orphan*/  addr_type; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  pend_le_reports; int /*<<< orphan*/  pend_le_conns; } ;
struct hci_conn_params {int explicit_connect; int auto_connect; int /*<<< orphan*/  action; } ;
struct hci_conn {int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
#define  HCI_AUTO_CONN_ALWAYS 131 
#define  HCI_AUTO_CONN_DIRECT 130 
#define  HCI_AUTO_CONN_EXPLICIT 129 
#define  HCI_AUTO_CONN_REPORT 128 
 int /*<<< orphan*/  hci_conn_params_del (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct smp_irk* hci_get_irk (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn_params* hci_pend_le_action_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_connect_le_scan_cleanup(struct hci_conn *conn)
{
	struct hci_conn_params *params;
	struct hci_dev *hdev = conn->hdev;
	struct smp_irk *irk;
	bdaddr_t *bdaddr;
	u8 bdaddr_type;

	bdaddr = &conn->dst;
	bdaddr_type = conn->dst_type;

	/* Check if we need to convert to identity address */
	irk = hci_get_irk(hdev, bdaddr, bdaddr_type);
	if (irk) {
		bdaddr = &irk->bdaddr;
		bdaddr_type = irk->addr_type;
	}

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, bdaddr,
					   bdaddr_type);
	if (!params || !params->explicit_connect)
		return;

	/* The connection attempt was doing scan for new RPA, and is
	 * in scan phase. If params are not associated with any other
	 * autoconnect action, remove them completely. If they are, just unmark
	 * them as waiting for connection, by clearing explicit_connect field.
	 */
	params->explicit_connect = false;

	list_del_init(&params->action);

	switch (params->auto_connect) {
	case HCI_AUTO_CONN_EXPLICIT:
		hci_conn_params_del(hdev, bdaddr, bdaddr_type);
		/* return instead of break to avoid duplicate scan update */
		return;
	case HCI_AUTO_CONN_DIRECT:
	case HCI_AUTO_CONN_ALWAYS:
		list_add(&params->action, &hdev->pend_le_conns);
		break;
	case HCI_AUTO_CONN_REPORT:
		list_add(&params->action, &hdev->pend_le_reports);
		break;
	default:
		break;
	}

	hci_update_background_scan(hdev);
}