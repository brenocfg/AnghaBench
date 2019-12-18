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
struct urb {struct snd_usb_caiaq_cb_info* context; } ;
struct snd_usb_caiaqdev {int output_running; int /*<<< orphan*/  outurb_active_mask; int /*<<< orphan*/  prepare_wait_queue; } ;
struct snd_usb_caiaq_cb_info {int /*<<< orphan*/  index; struct snd_usb_caiaqdev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_completed(struct urb *urb)
{
	struct snd_usb_caiaq_cb_info *info = urb->context;
	struct snd_usb_caiaqdev *cdev = info->cdev;

	if (!cdev->output_running) {
		cdev->output_running = 1;
		wake_up(&cdev->prepare_wait_queue);
	}

	clear_bit(info->index, &cdev->outurb_active_mask);
}