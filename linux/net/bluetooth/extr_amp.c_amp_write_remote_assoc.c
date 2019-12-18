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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  amp_write_rem_assoc_frag (struct hci_dev*,struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 

void amp_write_remote_assoc(struct hci_dev *hdev, u8 handle)
{
	struct hci_conn *hcon;

	BT_DBG("%s phy handle 0x%2.2x", hdev->name, handle);

	hcon = hci_conn_hash_lookup_handle(hdev, handle);
	if (!hcon)
		return;

	BT_DBG("%s phy handle 0x%2.2x hcon %p", hdev->name, handle, hcon);

	amp_write_rem_assoc_frag(hdev, hcon);
}