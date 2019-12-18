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
struct hci_conn {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hci_conn*) ; 
 struct hci_conn* to_hci_conn (struct device*) ; 

__attribute__((used)) static void bt_link_release(struct device *dev)
{
	struct hci_conn *conn = to_hci_conn(dev);
	kfree(conn);
}