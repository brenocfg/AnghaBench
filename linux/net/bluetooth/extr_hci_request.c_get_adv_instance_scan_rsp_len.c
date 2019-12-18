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
typedef  int u8 ;
struct hci_dev {int dummy; } ;
struct adv_info {int scan_rsp_len; } ;

/* Variables and functions */
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int) ; 

__attribute__((used)) static u8 get_adv_instance_scan_rsp_len(struct hci_dev *hdev, u8 instance)
{
	struct adv_info *adv_instance;

	/* Ignore instance 0 */
	if (instance == 0x00)
		return 0;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (!adv_instance)
		return 0;

	/* TODO: Take into account the "appearance" and "local-name" flags here.
	 * These are currently being ignored as they are not supported.
	 */
	return adv_instance->scan_rsp_len;
}