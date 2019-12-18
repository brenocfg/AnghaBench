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
struct hci_dev {int /*<<< orphan*/  debugfs; } ;
struct hci_conn {int handle; int /*<<< orphan*/  debugfs; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void hci_debugfs_create_conn(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;
	char name[6];

	if (IS_ERR_OR_NULL(hdev->debugfs))
		return;

	snprintf(name, sizeof(name), "%u", conn->handle);
	conn->debugfs = debugfs_create_dir(name, hdev->debugfs);
}