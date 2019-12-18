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
struct hci_conn {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  enable_6lowpan ; 

__attribute__((used)) static bool is_bt_6lowpan(struct hci_conn *hcon)
{
	if (hcon->type != LE_LINK)
		return false;

	if (!enable_6lowpan)
		return false;

	return true;
}