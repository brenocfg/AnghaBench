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
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 scalar_t__ known_fw_versions ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,scalar_t__,int) ; 

__attribute__((used)) static int usb6fire_fw_check(struct usb_interface *intf, const u8 *version)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(known_fw_versions); i++)
		if (!memcmp(version, known_fw_versions + i, 2))
			return 0;

	dev_err(&intf->dev, "invalid firmware version in device: %4ph. "
			"please reconnect to power. if this failure "
			"still happens, check your firmware installation.",
			version);
	return -EINVAL;
}