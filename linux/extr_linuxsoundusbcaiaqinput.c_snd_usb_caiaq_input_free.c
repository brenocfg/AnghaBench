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
struct snd_usb_caiaqdev {int /*<<< orphan*/ * input_dev; int /*<<< orphan*/ * ep4_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

void snd_usb_caiaq_input_free(struct snd_usb_caiaqdev *cdev)
{
	if (!cdev || !cdev->input_dev)
		return;

	usb_kill_urb(cdev->ep4_in_urb);
	usb_free_urb(cdev->ep4_in_urb);
	cdev->ep4_in_urb = NULL;

	input_unregister_device(cdev->input_dev);
	cdev->input_dev = NULL;
}