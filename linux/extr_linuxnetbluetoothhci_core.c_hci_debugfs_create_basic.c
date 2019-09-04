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
struct hci_dev {int /*<<< orphan*/  debugfs; scalar_t__ set_diag; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dut_mode_fops ; 
 int /*<<< orphan*/  vendor_diag_fops ; 

__attribute__((used)) static void hci_debugfs_create_basic(struct hci_dev *hdev)
{
	debugfs_create_file("dut_mode", 0644, hdev->debugfs, hdev,
			    &dut_mode_fops);

	if (hdev->set_diag)
		debugfs_create_file("vendor_diag", 0644, hdev->debugfs, hdev,
				    &vendor_diag_fops);
}