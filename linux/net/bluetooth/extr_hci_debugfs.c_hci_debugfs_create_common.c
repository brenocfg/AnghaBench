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
struct hci_dev {int /*<<< orphan*/  debugfs; scalar_t__ fw_info; scalar_t__ hw_info; int /*<<< orphan*/  hw_error_code; int /*<<< orphan*/  hci_rev; int /*<<< orphan*/  hci_ver; int /*<<< orphan*/  manufacturer; } ;

/* Variables and functions */
 int /*<<< orphan*/  blacklist_fops ; 
 int /*<<< orphan*/  conn_info_max_age_fops ; 
 int /*<<< orphan*/  conn_info_min_age_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u16 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_id_fops ; 
 int /*<<< orphan*/  device_list_fops ; 
 int /*<<< orphan*/  features_fops ; 
 int /*<<< orphan*/  firmware_info_fops ; 
 int /*<<< orphan*/  hardware_info_fops ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 scalar_t__ lmp_sc_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ssp_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  remote_oob_fops ; 
 int /*<<< orphan*/  sc_only_mode_fops ; 
 int /*<<< orphan*/  use_debug_keys_fops ; 
 int /*<<< orphan*/  uuids_fops ; 

void hci_debugfs_create_common(struct hci_dev *hdev)
{
	debugfs_create_file("features", 0444, hdev->debugfs, hdev,
			    &features_fops);
	debugfs_create_u16("manufacturer", 0444, hdev->debugfs,
			   &hdev->manufacturer);
	debugfs_create_u8("hci_version", 0444, hdev->debugfs, &hdev->hci_ver);
	debugfs_create_u16("hci_revision", 0444, hdev->debugfs, &hdev->hci_rev);
	debugfs_create_u8("hardware_error", 0444, hdev->debugfs,
			  &hdev->hw_error_code);
	debugfs_create_file("device_id", 0444, hdev->debugfs, hdev,
			    &device_id_fops);

	debugfs_create_file("device_list", 0444, hdev->debugfs, hdev,
			    &device_list_fops);
	debugfs_create_file("blacklist", 0444, hdev->debugfs, hdev,
			    &blacklist_fops);
	debugfs_create_file("uuids", 0444, hdev->debugfs, hdev, &uuids_fops);
	debugfs_create_file("remote_oob", 0400, hdev->debugfs, hdev,
			    &remote_oob_fops);

	debugfs_create_file("conn_info_min_age", 0644, hdev->debugfs, hdev,
			    &conn_info_min_age_fops);
	debugfs_create_file("conn_info_max_age", 0644, hdev->debugfs, hdev,
			    &conn_info_max_age_fops);

	if (lmp_ssp_capable(hdev) || lmp_le_capable(hdev))
		debugfs_create_file("use_debug_keys", 0444, hdev->debugfs,
				    hdev, &use_debug_keys_fops);

	if (lmp_sc_capable(hdev) || lmp_le_capable(hdev))
		debugfs_create_file("sc_only_mode", 0444, hdev->debugfs,
				    hdev, &sc_only_mode_fops);

	if (hdev->hw_info)
		debugfs_create_file("hardware_info", 0444, hdev->debugfs,
				    hdev, &hardware_info_fops);

	if (hdev->fw_info)
		debugfs_create_file("firmware_info", 0444, hdev->debugfs,
				    hdev, &firmware_info_fops);
}