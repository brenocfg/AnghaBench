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
struct sk_buff {scalar_t__ data; } ;
struct hci_evt_le_ext_adv_set_term {int /*<<< orphan*/  conn_handle; scalar_t__ status; } ;
struct hci_dev {scalar_t__ adv_addr_type; int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  random_addr; int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  resp_addr; } ;
struct adv_info {int /*<<< orphan*/  random_addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_LE_DEV_RANDOM ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_le_ext_adv_term_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_evt_le_ext_adv_set_term *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	if (ev->status)
		return;

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->conn_handle));
	if (conn) {
		struct adv_info *adv_instance;

		if (hdev->adv_addr_type != ADDR_LE_DEV_RANDOM)
			return;

		if (!hdev->cur_adv_instance) {
			bacpy(&conn->resp_addr, &hdev->random_addr);
			return;
		}

		adv_instance = hci_find_adv_instance(hdev, hdev->cur_adv_instance);
		if (adv_instance)
			bacpy(&conn->resp_addr, &adv_instance->random_addr);
	}
}