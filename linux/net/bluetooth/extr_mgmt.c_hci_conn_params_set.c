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
typedef  int u8 ;
struct hci_dev {int /*<<< orphan*/  pend_le_conns; int /*<<< orphan*/  pend_le_reports; } ;
struct hci_conn_params {int auto_connect; int /*<<< orphan*/  action; int /*<<< orphan*/  explicit_connect; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ *,int,int) ; 
 int EIO ; 
#define  HCI_AUTO_CONN_ALWAYS 132 
#define  HCI_AUTO_CONN_DIRECT 131 
#define  HCI_AUTO_CONN_DISABLED 130 
#define  HCI_AUTO_CONN_LINK_LOSS 129 
#define  HCI_AUTO_CONN_REPORT 128 
 struct hci_conn_params* hci_conn_params_add (struct hci_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_connected (struct hci_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_conn_params_set(struct hci_dev *hdev, bdaddr_t *addr,
			       u8 addr_type, u8 auto_connect)
{
	struct hci_conn_params *params;

	params = hci_conn_params_add(hdev, addr, addr_type);
	if (!params)
		return -EIO;

	if (params->auto_connect == auto_connect)
		return 0;

	list_del_init(&params->action);

	switch (auto_connect) {
	case HCI_AUTO_CONN_DISABLED:
	case HCI_AUTO_CONN_LINK_LOSS:
		/* If auto connect is being disabled when we're trying to
		 * connect to device, keep connecting.
		 */
		if (params->explicit_connect)
			list_add(&params->action, &hdev->pend_le_conns);
		break;
	case HCI_AUTO_CONN_REPORT:
		if (params->explicit_connect)
			list_add(&params->action, &hdev->pend_le_conns);
		else
			list_add(&params->action, &hdev->pend_le_reports);
		break;
	case HCI_AUTO_CONN_DIRECT:
	case HCI_AUTO_CONN_ALWAYS:
		if (!is_connected(hdev, addr, addr_type))
			list_add(&params->action, &hdev->pend_le_conns);
		break;
	}

	params->auto_connect = auto_connect;

	BT_DBG("addr %pMR (type %u) auto_connect %u", addr, addr_type,
	       auto_connect);

	return 0;
}