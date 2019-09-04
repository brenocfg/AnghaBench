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
struct zd_usb {int /*<<< orphan*/  intf; scalar_t__ was_running; } ;
struct zd_mac {scalar_t__ type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  ZD_DEVICE_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_queue_reset_device (int /*<<< orphan*/ ) ; 
 int zd_op_start (int /*<<< orphan*/ ) ; 
 int zd_restore_settings (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_to_hw (struct zd_usb*) ; 
 struct zd_mac* zd_usb_to_mac (struct zd_usb*) ; 

__attribute__((used)) static void zd_usb_resume(struct zd_usb *usb)
{
	struct zd_mac *mac = zd_usb_to_mac(usb);
	int r;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	r = zd_op_start(zd_usb_to_hw(usb));
	if (r < 0) {
		dev_warn(zd_usb_dev(usb), "Device resume failed "
			 "with error code %d. Retrying...\n", r);
		if (usb->was_running)
			set_bit(ZD_DEVICE_RUNNING, &mac->flags);
		usb_queue_reset_device(usb->intf);
		return;
	}

	if (mac->type != NL80211_IFTYPE_UNSPECIFIED) {
		r = zd_restore_settings(mac);
		if (r < 0) {
			dev_dbg(zd_usb_dev(usb),
				"failed to restore settings, %d\n", r);
			return;
		}
	}
}