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
typedef  int /*<<< orphan*/  u16 ;
struct hci_dev {int /*<<< orphan*/  short_name; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  appearance; int /*<<< orphan*/  dev_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIR_APPEARANCE ; 
 int /*<<< orphan*/  EIR_CLASS_OF_DEV ; 
 int /*<<< orphan*/  EIR_NAME_COMPLETE ; 
 int /*<<< orphan*/  EIR_NAME_SHORT ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  eir_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  eir_append_le16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 append_eir_data_to_buf(struct hci_dev *hdev, u8 *eir)
{
	u16 eir_len = 0;
	size_t name_len;

	if (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		eir_len = eir_append_data(eir, eir_len, EIR_CLASS_OF_DEV,
					  hdev->dev_class, 3);

	if (hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		eir_len = eir_append_le16(eir, eir_len, EIR_APPEARANCE,
					  hdev->appearance);

	name_len = strlen(hdev->dev_name);
	eir_len = eir_append_data(eir, eir_len, EIR_NAME_COMPLETE,
				  hdev->dev_name, name_len);

	name_len = strlen(hdev->short_name);
	eir_len = eir_append_data(eir, eir_len, EIR_NAME_SHORT,
				  hdev->short_name, name_len);

	return eir_len;
}