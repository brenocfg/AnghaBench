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
struct hci_dev {scalar_t__ inq_tx_power; scalar_t__ devid_source; scalar_t__ devid_vendor; scalar_t__ devid_product; scalar_t__ devid_version; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int EIR_DEVICE_ID ; 
 int EIR_NAME_COMPLETE ; 
 int EIR_NAME_SHORT ; 
 int EIR_TX_POWER ; 
 scalar_t__ HCI_MAX_EIR_LENGTH ; 
 scalar_t__ HCI_TX_POWER_INVALID ; 
 int* create_uuid128_list (struct hci_dev*,int*,scalar_t__) ; 
 int* create_uuid16_list (struct hci_dev*,int*,scalar_t__) ; 
 int* create_uuid32_list (struct hci_dev*,int*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  put_unaligned_le16 (scalar_t__,int*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_eir(struct hci_dev *hdev, u8 *data)
{
	u8 *ptr = data;
	size_t name_len;

	name_len = strlen(hdev->dev_name);

	if (name_len > 0) {
		/* EIR Data type */
		if (name_len > 48) {
			name_len = 48;
			ptr[1] = EIR_NAME_SHORT;
		} else
			ptr[1] = EIR_NAME_COMPLETE;

		/* EIR Data length */
		ptr[0] = name_len + 1;

		memcpy(ptr + 2, hdev->dev_name, name_len);

		ptr += (name_len + 2);
	}

	if (hdev->inq_tx_power != HCI_TX_POWER_INVALID) {
		ptr[0] = 2;
		ptr[1] = EIR_TX_POWER;
		ptr[2] = (u8) hdev->inq_tx_power;

		ptr += 3;
	}

	if (hdev->devid_source > 0) {
		ptr[0] = 9;
		ptr[1] = EIR_DEVICE_ID;

		put_unaligned_le16(hdev->devid_source, ptr + 2);
		put_unaligned_le16(hdev->devid_vendor, ptr + 4);
		put_unaligned_le16(hdev->devid_product, ptr + 6);
		put_unaligned_le16(hdev->devid_version, ptr + 8);

		ptr += 10;
	}

	ptr = create_uuid16_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
	ptr = create_uuid32_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
	ptr = create_uuid128_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
}