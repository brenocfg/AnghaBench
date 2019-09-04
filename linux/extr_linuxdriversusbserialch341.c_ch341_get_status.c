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
struct usb_device {int dummy; } ;
struct ch341_private {char msr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 char CH341_BITS_MODEM_STAT ; 
 int /*<<< orphan*/  CH341_REQ_READ_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_control_in (struct usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,unsigned int const) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ch341_get_status(struct usb_device *dev, struct ch341_private *priv)
{
	const unsigned int size = 2;
	char *buffer;
	int r;
	unsigned long flags;

	buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	r = ch341_control_in(dev, CH341_REQ_READ_REG, 0x0706, 0, buffer, size);
	if (r < 0)
		goto out;

	spin_lock_irqsave(&priv->lock, flags);
	priv->msr = (~(*buffer)) & CH341_BITS_MODEM_STAT;
	spin_unlock_irqrestore(&priv->lock, flags);

out:	kfree(buffer);
	return r;
}