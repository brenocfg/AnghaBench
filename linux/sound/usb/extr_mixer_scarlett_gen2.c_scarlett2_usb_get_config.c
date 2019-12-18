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
struct usb_mixer_interface {int dummy; } ;
struct scarlett2_config {int size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 struct scarlett2_config* scarlett2_config_items ; 
 int scarlett2_usb_get (struct usb_mixer_interface*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int scarlett2_usb_get_config(
	struct usb_mixer_interface *mixer,
	int config_item_num, int count, void *buf)
{
	const struct scarlett2_config config_item =
	       scarlett2_config_items[config_item_num];
	int size = config_item.size * count;

	return scarlett2_usb_get(mixer, config_item.offset, buf, size);
}