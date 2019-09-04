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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct discovery_state {void* last_adv_data_len; int /*<<< orphan*/  last_adv_data; int /*<<< orphan*/  last_adv_flags; int /*<<< orphan*/  last_adv_rssi; void* last_adv_addr_type; int /*<<< orphan*/  last_adv_addr; } ;
struct hci_dev {struct discovery_state discovery; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 

__attribute__((used)) static void store_pending_adv_report(struct hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 bdaddr_type, s8 rssi, u32 flags,
				     u8 *data, u8 len)
{
	struct discovery_state *d = &hdev->discovery;

	bacpy(&d->last_adv_addr, bdaddr);
	d->last_adv_addr_type = bdaddr_type;
	d->last_adv_rssi = rssi;
	d->last_adv_flags = flags;
	memcpy(d->last_adv_data, data, len);
	d->last_adv_data_len = len;
}