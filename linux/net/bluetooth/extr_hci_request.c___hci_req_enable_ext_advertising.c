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
typedef  int u16 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct hci_cp_le_set_ext_adv_enable {int enable; int num_of_sets; int /*<<< orphan*/  duration; int /*<<< orphan*/  handle; scalar_t__ data; } ;
struct hci_cp_ext_adv_set {int enable; int num_of_sets; int /*<<< orphan*/  duration; int /*<<< orphan*/  handle; scalar_t__ data; } ;
struct adv_info {int duration; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_ADV_ENABLE ; 
 int MSEC_PER_SEC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_ext_adv_enable*,int /*<<< orphan*/ ,int) ; 

int __hci_req_enable_ext_advertising(struct hci_request *req, u8 instance)
{
	struct hci_dev *hdev = req->hdev;
	struct hci_cp_le_set_ext_adv_enable *cp;
	struct hci_cp_ext_adv_set *adv_set;
	u8 data[sizeof(*cp) + sizeof(*adv_set) * 1];
	struct adv_info *adv_instance;

	if (instance > 0) {
		adv_instance = hci_find_adv_instance(hdev, instance);
		if (!adv_instance)
			return -EINVAL;
	} else {
		adv_instance = NULL;
	}

	cp = (void *) data;
	adv_set = (void *) cp->data;

	memset(cp, 0, sizeof(*cp));

	cp->enable = 0x01;
	cp->num_of_sets = 0x01;

	memset(adv_set, 0, sizeof(*adv_set));

	adv_set->handle = instance;

	/* Set duration per instance since controller is responsible for
	 * scheduling it.
	 */
	if (adv_instance && adv_instance->duration) {
		u16 duration = adv_instance->duration * MSEC_PER_SEC;

		/* Time = N * 10 ms */
		adv_set->duration = cpu_to_le16(duration / 10);
	}

	hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_ENABLE,
		    sizeof(*cp) + sizeof(*adv_set) * cp->num_of_sets,
		    data);

	return 0;
}