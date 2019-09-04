#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ active; } ;
struct usb_line6 {TYPE_1__ messages; } ;
struct snd_hwdep {struct usb_line6* private_data; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int line6_hwdep_release(struct snd_hwdep *hw, struct file *file)
{
	struct usb_line6 *line6 = hw->private_data;

	line6->messages.active = 0;

	return 0;
}