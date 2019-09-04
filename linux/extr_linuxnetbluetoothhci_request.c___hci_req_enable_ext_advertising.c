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
struct hci_request {int dummy; } ;
struct hci_cp_le_set_ext_adv_enable {int enable; int num_of_sets; scalar_t__ handle; scalar_t__ data; } ;
struct hci_cp_ext_adv_set {int enable; int num_of_sets; scalar_t__ handle; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_ADV_ENABLE ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_ext_adv_enable*,int /*<<< orphan*/ ,int) ; 

void __hci_req_enable_ext_advertising(struct hci_request *req)
{
	struct hci_cp_le_set_ext_adv_enable *cp;
	struct hci_cp_ext_adv_set *adv_set;
	u8 data[sizeof(*cp) + sizeof(*adv_set) * 1];

	cp = (void *) data;
	adv_set = (void *) cp->data;

	memset(cp, 0, sizeof(*cp));

	cp->enable = 0x01;
	cp->num_of_sets = 0x01;

	memset(adv_set, 0, sizeof(*adv_set));

	adv_set->handle = 0;

	hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_ENABLE,
		    sizeof(*cp) + sizeof(*adv_set) * cp->num_of_sets,
		    data);
}