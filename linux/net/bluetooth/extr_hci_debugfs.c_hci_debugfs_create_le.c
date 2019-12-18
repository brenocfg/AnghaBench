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
struct hci_dev {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  discov_interleaved_timeout; int /*<<< orphan*/  le_resolv_list_size; int /*<<< orphan*/  le_white_list_size; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  adv_channel_map_fops ; 
 int /*<<< orphan*/  adv_max_interval_fops ; 
 int /*<<< orphan*/  adv_min_interval_fops ; 
 int /*<<< orphan*/  auth_payload_timeout_fops ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_latency_fops ; 
 int /*<<< orphan*/  conn_max_interval_fops ; 
 int /*<<< orphan*/  conn_min_interval_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u16 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  force_static_address_fops ; 
 int /*<<< orphan*/  identity_fops ; 
 int /*<<< orphan*/  identity_resolving_keys_fops ; 
 int /*<<< orphan*/  long_term_keys_fops ; 
 int /*<<< orphan*/  quirk_simultaneous_discovery_fops ; 
 int /*<<< orphan*/  quirk_strict_duplicate_filter_fops ; 
 int /*<<< orphan*/  random_address_fops ; 
 int /*<<< orphan*/  resolv_list_fops ; 
 int /*<<< orphan*/  rpa_timeout_fops ; 
 int /*<<< orphan*/  static_address_fops ; 
 int /*<<< orphan*/  supervision_timeout_fops ; 
 int /*<<< orphan*/  white_list_fops ; 

void hci_debugfs_create_le(struct hci_dev *hdev)
{
	debugfs_create_file("identity", 0400, hdev->debugfs, hdev,
			    &identity_fops);
	debugfs_create_file("rpa_timeout", 0644, hdev->debugfs, hdev,
			    &rpa_timeout_fops);
	debugfs_create_file("random_address", 0444, hdev->debugfs, hdev,
			    &random_address_fops);
	debugfs_create_file("static_address", 0444, hdev->debugfs, hdev,
			    &static_address_fops);

	/* For controllers with a public address, provide a debug
	 * option to force the usage of the configured static
	 * address. By default the public address is used.
	 */
	if (bacmp(&hdev->bdaddr, BDADDR_ANY))
		debugfs_create_file("force_static_address", 0644,
				    hdev->debugfs, hdev,
				    &force_static_address_fops);

	debugfs_create_u8("white_list_size", 0444, hdev->debugfs,
			  &hdev->le_white_list_size);
	debugfs_create_file("white_list", 0444, hdev->debugfs, hdev,
			    &white_list_fops);
	debugfs_create_u8("resolv_list_size", 0444, hdev->debugfs,
			  &hdev->le_resolv_list_size);
	debugfs_create_file("resolv_list", 0444, hdev->debugfs, hdev,
			    &resolv_list_fops);
	debugfs_create_file("identity_resolving_keys", 0400, hdev->debugfs,
			    hdev, &identity_resolving_keys_fops);
	debugfs_create_file("long_term_keys", 0400, hdev->debugfs, hdev,
			    &long_term_keys_fops);
	debugfs_create_file("conn_min_interval", 0644, hdev->debugfs, hdev,
			    &conn_min_interval_fops);
	debugfs_create_file("conn_max_interval", 0644, hdev->debugfs, hdev,
			    &conn_max_interval_fops);
	debugfs_create_file("conn_latency", 0644, hdev->debugfs, hdev,
			    &conn_latency_fops);
	debugfs_create_file("supervision_timeout", 0644, hdev->debugfs, hdev,
			    &supervision_timeout_fops);
	debugfs_create_file("adv_channel_map", 0644, hdev->debugfs, hdev,
			    &adv_channel_map_fops);
	debugfs_create_file("adv_min_interval", 0644, hdev->debugfs, hdev,
			    &adv_min_interval_fops);
	debugfs_create_file("adv_max_interval", 0644, hdev->debugfs, hdev,
			    &adv_max_interval_fops);
	debugfs_create_u16("discov_interleaved_timeout", 0644, hdev->debugfs,
			   &hdev->discov_interleaved_timeout);
	debugfs_create_file("auth_payload_timeout", 0644, hdev->debugfs, hdev,
			    &auth_payload_timeout_fops);

	debugfs_create_file("quirk_strict_duplicate_filter", 0644,
			    hdev->debugfs, hdev,
			    &quirk_strict_duplicate_filter_fops);
	debugfs_create_file("quirk_simultaneous_discovery", 0644,
			    hdev->debugfs, hdev,
			    &quirk_simultaneous_discovery_fops);
}