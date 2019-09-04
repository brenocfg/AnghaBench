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
typedef  scalar_t__ u32 ;
struct smp_irk {int addr_type; int /*<<< orphan*/  bdaddr; } ;
struct discovery_state {int last_adv_addr_type; int* last_adv_data; int last_adv_data_len; scalar_t__ last_adv_flags; int /*<<< orphan*/  last_adv_addr; int /*<<< orphan*/  last_adv_rssi; } ;
struct hci_dev {scalar_t__ le_scan_type; int /*<<< orphan*/  pend_le_reports; int /*<<< orphan*/  irk; struct discovery_state discovery; } ;
struct hci_conn {int le_adv_data_len; int /*<<< orphan*/  le_adv_data; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_PRIVACY ; 
#define  LE_ADV_DIRECT_IND 132 
#define  LE_ADV_IND 131 
#define  LE_ADV_NONCONN_IND 130 
#define  LE_ADV_SCAN_IND 129 
#define  LE_ADV_SCAN_RSP 128 
 int /*<<< orphan*/  LE_LINK ; 
 scalar_t__ LE_SCAN_PASSIVE ; 
 scalar_t__ MGMT_DEV_FOUND_NOT_CONNECTABLE ; 
 int /*<<< orphan*/  bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err_ratelimited (struct hci_dev*,char*,...) ; 
 struct hci_conn* check_pending_le_conn (struct hci_dev*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pending_adv_report (struct hci_dev*) ; 
 int /*<<< orphan*/  has_pending_adv_report (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_bdaddr_is_rpa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct smp_irk* hci_get_irk (struct hci_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_pend_le_action_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mgmt_device_found (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*,int,int*,int) ; 
 int /*<<< orphan*/  smp_irk_matches (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_pending_adv_report (struct hci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int*,int) ; 

__attribute__((used)) static void process_adv_report(struct hci_dev *hdev, u8 type, bdaddr_t *bdaddr,
			       u8 bdaddr_type, bdaddr_t *direct_addr,
			       u8 direct_addr_type, s8 rssi, u8 *data, u8 len)
{
	struct discovery_state *d = &hdev->discovery;
	struct smp_irk *irk;
	struct hci_conn *conn;
	bool match;
	u32 flags;
	u8 *ptr, real_len;

	switch (type) {
	case LE_ADV_IND:
	case LE_ADV_DIRECT_IND:
	case LE_ADV_SCAN_IND:
	case LE_ADV_NONCONN_IND:
	case LE_ADV_SCAN_RSP:
		break;
	default:
		bt_dev_err_ratelimited(hdev, "unknown advertising packet "
				       "type: 0x%02x", type);
		return;
	}

	/* Find the end of the data in case the report contains padded zero
	 * bytes at the end causing an invalid length value.
	 *
	 * When data is NULL, len is 0 so there is no need for extra ptr
	 * check as 'ptr < data + 0' is already false in such case.
	 */
	for (ptr = data; ptr < data + len && *ptr; ptr += *ptr + 1) {
		if (ptr + 1 + *ptr > data + len)
			break;
	}

	real_len = ptr - data;

	/* Adjust for actual length */
	if (len != real_len) {
		bt_dev_err_ratelimited(hdev, "advertising data len corrected");
		len = real_len;
	}

	/* If the direct address is present, then this report is from
	 * a LE Direct Advertising Report event. In that case it is
	 * important to see if the address is matching the local
	 * controller address.
	 */
	if (direct_addr) {
		/* Only resolvable random addresses are valid for these
		 * kind of reports and others can be ignored.
		 */
		if (!hci_bdaddr_is_rpa(direct_addr, direct_addr_type))
			return;

		/* If the controller is not using resolvable random
		 * addresses, then this report can be ignored.
		 */
		if (!hci_dev_test_flag(hdev, HCI_PRIVACY))
			return;

		/* If the local IRK of the controller does not match
		 * with the resolvable random address provided, then
		 * this report can be ignored.
		 */
		if (!smp_irk_matches(hdev, hdev->irk, direct_addr))
			return;
	}

	/* Check if we need to convert to identity address */
	irk = hci_get_irk(hdev, bdaddr, bdaddr_type);
	if (irk) {
		bdaddr = &irk->bdaddr;
		bdaddr_type = irk->addr_type;
	}

	/* Check if we have been requested to connect to this device.
	 *
	 * direct_addr is set only for directed advertising reports (it is NULL
	 * for advertising reports) and is already verified to be RPA above.
	 */
	conn = check_pending_le_conn(hdev, bdaddr, bdaddr_type, type,
								direct_addr);
	if (conn && type == LE_ADV_IND) {
		/* Store report for later inclusion by
		 * mgmt_device_connected
		 */
		memcpy(conn->le_adv_data, data, len);
		conn->le_adv_data_len = len;
	}

	/* Passive scanning shouldn't trigger any device found events,
	 * except for devices marked as CONN_REPORT for which we do send
	 * device found events.
	 */
	if (hdev->le_scan_type == LE_SCAN_PASSIVE) {
		if (type == LE_ADV_DIRECT_IND)
			return;

		if (!hci_pend_le_action_lookup(&hdev->pend_le_reports,
					       bdaddr, bdaddr_type))
			return;

		if (type == LE_ADV_NONCONN_IND || type == LE_ADV_SCAN_IND)
			flags = MGMT_DEV_FOUND_NOT_CONNECTABLE;
		else
			flags = 0;
		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, NULL,
				  rssi, flags, data, len, NULL, 0);
		return;
	}

	/* When receiving non-connectable or scannable undirected
	 * advertising reports, this means that the remote device is
	 * not connectable and then clearly indicate this in the
	 * device found event.
	 *
	 * When receiving a scan response, then there is no way to
	 * know if the remote device is connectable or not. However
	 * since scan responses are merged with a previously seen
	 * advertising report, the flags field from that report
	 * will be used.
	 *
	 * In the really unlikely case that a controller get confused
	 * and just sends a scan response event, then it is marked as
	 * not connectable as well.
	 */
	if (type == LE_ADV_NONCONN_IND || type == LE_ADV_SCAN_IND ||
	    type == LE_ADV_SCAN_RSP)
		flags = MGMT_DEV_FOUND_NOT_CONNECTABLE;
	else
		flags = 0;

	/* If there's nothing pending either store the data from this
	 * event or send an immediate device found event if the data
	 * should not be stored for later.
	 */
	if (!has_pending_adv_report(hdev)) {
		/* If the report will trigger a SCAN_REQ store it for
		 * later merging.
		 */
		if (type == LE_ADV_IND || type == LE_ADV_SCAN_IND) {
			store_pending_adv_report(hdev, bdaddr, bdaddr_type,
						 rssi, flags, data, len);
			return;
		}

		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, NULL,
				  rssi, flags, data, len, NULL, 0);
		return;
	}

	/* Check if the pending report is for the same device as the new one */
	match = (!bacmp(bdaddr, &d->last_adv_addr) &&
		 bdaddr_type == d->last_adv_addr_type);

	/* If the pending data doesn't match this report or this isn't a
	 * scan response (e.g. we got a duplicate ADV_IND) then force
	 * sending of the pending data.
	 */
	if (type != LE_ADV_SCAN_RSP || !match) {
		/* Send out whatever is in the cache, but skip duplicates */
		if (!match)
			mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
					  d->last_adv_addr_type, NULL,
					  d->last_adv_rssi, d->last_adv_flags,
					  d->last_adv_data,
					  d->last_adv_data_len, NULL, 0);

		/* If the new report will trigger a SCAN_REQ store it for
		 * later merging.
		 */
		if (type == LE_ADV_IND || type == LE_ADV_SCAN_IND) {
			store_pending_adv_report(hdev, bdaddr, bdaddr_type,
						 rssi, flags, data, len);
			return;
		}

		/* The advertising reports cannot be merged, so clear
		 * the pending report and send out a device found event.
		 */
		clear_pending_adv_report(hdev);
		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, NULL,
				  rssi, flags, data, len, NULL, 0);
		return;
	}

	/* If we get here we've got a pending ADV_IND or ADV_SCAN_IND and
	 * the new event is a SCAN_RSP. We can therefore proceed with
	 * sending a merged device found event.
	 */
	mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
			  d->last_adv_addr_type, NULL, rssi, d->last_adv_flags,
			  d->last_adv_data, d->last_adv_data_len, data, len);
	clear_pending_adv_report(hdev);
}