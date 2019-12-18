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

/* Variables and functions */
 int /*<<< orphan*/  auto_accept_delay_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_class_fops ; 
 int /*<<< orphan*/  idle_timeout_fops ; 
 int /*<<< orphan*/  inquiry_cache_fops ; 
 int /*<<< orphan*/  link_keys_fops ; 
 scalar_t__ lmp_sniff_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ssp_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  min_encrypt_key_size_fops ; 
 int /*<<< orphan*/  sniff_max_interval_fops ; 
 int /*<<< orphan*/  sniff_min_interval_fops ; 
 int /*<<< orphan*/  ssp_debug_mode_fops ; 
 int /*<<< orphan*/  voice_setting_fops ; 

void hci_debugfs_create_bredr(struct hci_dev *hdev)
{
	debugfs_create_file("inquiry_cache", 0444, hdev->debugfs, hdev,
			    &inquiry_cache_fops);
	debugfs_create_file("link_keys", 0400, hdev->debugfs, hdev,
			    &link_keys_fops);
	debugfs_create_file("dev_class", 0444, hdev->debugfs, hdev,
			    &dev_class_fops);
	debugfs_create_file("voice_setting", 0444, hdev->debugfs, hdev,
			    &voice_setting_fops);

	if (lmp_ssp_capable(hdev)) {
		debugfs_create_file("ssp_debug_mode", 0444, hdev->debugfs,
				    hdev, &ssp_debug_mode_fops);
		debugfs_create_file("min_encrypt_key_size", 0644, hdev->debugfs,
				    hdev, &min_encrypt_key_size_fops);
		debugfs_create_file("auto_accept_delay", 0644, hdev->debugfs,
				    hdev, &auto_accept_delay_fops);
	}

	if (lmp_sniff_capable(hdev)) {
		debugfs_create_file("idle_timeout", 0644, hdev->debugfs,
				    hdev, &idle_timeout_fops);
		debugfs_create_file("sniff_min_interval", 0644, hdev->debugfs,
				    hdev, &sniff_min_interval_fops);
		debugfs_create_file("sniff_max_interval", 0644, hdev->debugfs,
				    hdev, &sniff_max_interval_fops);
	}
}