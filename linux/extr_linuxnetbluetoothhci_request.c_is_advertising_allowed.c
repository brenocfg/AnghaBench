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
struct TYPE_2__ {scalar_t__ le_num_slave; } ;
struct hci_dev {int* le_states; TYPE_1__ conn_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_LINK ; 
 scalar_t__ hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_advertising_allowed(struct hci_dev *hdev, bool connectable)
{
	/* If there is no connection we are OK to advertise. */
	if (hci_conn_num(hdev, LE_LINK) == 0)
		return true;

	/* Check le_states if there is any connection in slave role. */
	if (hdev->conn_hash.le_num_slave > 0) {
		/* Slave connection state and non connectable mode bit 20. */
		if (!connectable && !(hdev->le_states[2] & 0x10))
			return false;

		/* Slave connection state and connectable mode bit 38
		 * and scannable bit 21.
		 */
		if (connectable && (!(hdev->le_states[4] & 0x40) ||
				    !(hdev->le_states[2] & 0x20)))
			return false;
	}

	/* Check le_states if there is any connection in master role. */
	if (hci_conn_num(hdev, LE_LINK) != hdev->conn_hash.le_num_slave) {
		/* Master connection state and non connectable mode bit 18. */
		if (!connectable && !(hdev->le_states[2] & 0x02))
			return false;

		/* Master connection state and connectable mode bit 35 and
		 * scannable 19.
		 */
		if (connectable && (!(hdev->le_states[4] & 0x08) ||
				    !(hdev->le_states[2] & 0x08)))
			return false;
	}

	return true;
}