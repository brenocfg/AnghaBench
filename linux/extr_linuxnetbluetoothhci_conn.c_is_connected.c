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
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_connected(struct hci_dev *hdev, bdaddr_t *addr, u8 type)
{
	struct hci_conn *conn;

	conn = hci_conn_hash_lookup_le(hdev, addr, type);
	if (!conn)
		return false;

	if (conn->state != BT_CONNECTED)
		return false;

	return true;
}