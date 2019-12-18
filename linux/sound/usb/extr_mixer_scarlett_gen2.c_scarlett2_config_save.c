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
typedef  int /*<<< orphan*/  u32 ;
struct usb_mixer_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_USB_CONFIG_SAVE ; 
 int /*<<< orphan*/  SCARLETT2_USB_DATA_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scarlett2_usb (struct usb_mixer_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scarlett2_config_save(struct usb_mixer_interface *mixer)
{
	u32 req = cpu_to_le32(SCARLETT2_USB_CONFIG_SAVE);

	scarlett2_usb(mixer, SCARLETT2_USB_DATA_CMD,
		      &req, sizeof(u32),
		      NULL, 0);
}