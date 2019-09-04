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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_dev_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_usb_reset_device(struct device *dev, void *notused)
{
	/* device past is the usb interface so we
	 * need to use parent here.
	 */
	brcmf_dev_reset(dev->parent);
	return 0;
}