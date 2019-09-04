#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ rssi; scalar_t__ uuid_count; int /*<<< orphan*/  uuids; } ;
struct hci_dev {TYPE_1__ discovery; int /*<<< orphan*/  quirks; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_STRICT_DUPLICATE_FILTER ; 
 scalar_t__ HCI_RSSI_INVALID ; 
 int /*<<< orphan*/  eir_has_uuids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restart_le_scan (struct hci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_filter_match(struct hci_dev *hdev, s8 rssi, u8 *eir,
			    u16 eir_len, u8 *scan_rsp, u8 scan_rsp_len)
{
	/* If a RSSI threshold has been specified, and
	 * HCI_QUIRK_STRICT_DUPLICATE_FILTER is not set, then all results with
	 * a RSSI smaller than the RSSI threshold will be dropped. If the quirk
	 * is set, let it through for further processing, as we might need to
	 * restart the scan.
	 *
	 * For BR/EDR devices (pre 1.2) providing no RSSI during inquiry,
	 * the results are also dropped.
	 */
	if (hdev->discovery.rssi != HCI_RSSI_INVALID &&
	    (rssi == HCI_RSSI_INVALID ||
	    (rssi < hdev->discovery.rssi &&
	     !test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks))))
		return  false;

	if (hdev->discovery.uuid_count != 0) {
		/* If a list of UUIDs is provided in filter, results with no
		 * matching UUID should be dropped.
		 */
		if (!eir_has_uuids(eir, eir_len, hdev->discovery.uuid_count,
				   hdev->discovery.uuids) &&
		    !eir_has_uuids(scan_rsp, scan_rsp_len,
				   hdev->discovery.uuid_count,
				   hdev->discovery.uuids))
			return false;
	}

	/* If duplicate filtering does not report RSSI changes, then restart
	 * scanning to ensure updated result with updated RSSI values.
	 */
	if (test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks)) {
		restart_le_scan(hdev);

		/* Validate RSSI value against the RSSI threshold once more. */
		if (hdev->discovery.rssi != HCI_RSSI_INVALID &&
		    rssi < hdev->discovery.rssi)
			return false;
	}

	return true;
}