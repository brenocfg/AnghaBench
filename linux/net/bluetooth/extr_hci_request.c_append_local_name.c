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
struct hci_dev {int* dev_name; int* short_name; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  EIR_NAME_COMPLETE ; 
 int /*<<< orphan*/  EIR_NAME_SHORT ; 
 int HCI_MAX_AD_LENGTH ; 
 int HCI_MAX_SHORT_NAME_LENGTH ; 
 int eir_append_data (int*,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 size_t strlen (int*) ; 

u8 append_local_name(struct hci_dev *hdev, u8 *ptr, u8 ad_len)
{
	size_t short_len;
	size_t complete_len;

	/* no space left for name (+ NULL + type + len) */
	if ((HCI_MAX_AD_LENGTH - ad_len) < HCI_MAX_SHORT_NAME_LENGTH + 3)
		return ad_len;

	/* use complete name if present and fits */
	complete_len = strlen(hdev->dev_name);
	if (complete_len && complete_len <= HCI_MAX_SHORT_NAME_LENGTH)
		return eir_append_data(ptr, ad_len, EIR_NAME_COMPLETE,
				       hdev->dev_name, complete_len + 1);

	/* use short name if present */
	short_len = strlen(hdev->short_name);
	if (short_len)
		return eir_append_data(ptr, ad_len, EIR_NAME_SHORT,
				       hdev->short_name, short_len + 1);

	/* use shortened full name if present, we already know that name
	 * is longer then HCI_MAX_SHORT_NAME_LENGTH
	 */
	if (complete_len) {
		u8 name[HCI_MAX_SHORT_NAME_LENGTH + 1];

		memcpy(name, hdev->dev_name, HCI_MAX_SHORT_NAME_LENGTH);
		name[HCI_MAX_SHORT_NAME_LENGTH] = '\0';

		return eir_append_data(ptr, ad_len, EIR_NAME_SHORT, name,
				       sizeof(name));
	}

	return ad_len;
}