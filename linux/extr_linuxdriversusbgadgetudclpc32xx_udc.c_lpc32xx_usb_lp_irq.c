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
typedef  int u32 ;
struct lpc32xx_udc {int enabled_devints; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  udp_baseaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RD_ERR_STAT ; 
 int /*<<< orphan*/  DAT_RD_ERR_STAT ; 
 int ERR_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTST (int /*<<< orphan*/ ) ; 
 int USBD_DEV_STAT ; 
 int USBD_EP_FAST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_handle_dev (struct lpc32xx_udc*) ; 
 int udc_protocol_cmd_r (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpc32xx_usb_lp_irq(int irq, void *_udc)
{
	u32 tmp, devstat;
	struct lpc32xx_udc *udc = _udc;

	spin_lock(&udc->lock);

	/* Read the device status register */
	devstat = readl(USBD_DEVINTST(udc->udp_baseaddr));

	devstat &= ~USBD_EP_FAST;
	writel(devstat, USBD_DEVINTCLR(udc->udp_baseaddr));
	devstat = devstat & udc->enabled_devints;

	/* Device specific handling needed? */
	if (devstat & USBD_DEV_STAT)
		udc_handle_dev(udc);

	/* Start of frame? (devstat & FRAME_INT):
	 * The frame interrupt isn't really needed for ISO support,
	 * as the driver will queue the necessary packets */

	/* Error? */
	if (devstat & ERR_INT) {
		/* All types of errors, from cable removal during transfer to
		 * misc protocol and bit errors. These are mostly for just info,
		 * as the USB hardware will work around these. If these errors
		 * happen alot, something is wrong. */
		udc_protocol_cmd_w(udc, CMD_RD_ERR_STAT);
		tmp = udc_protocol_cmd_r(udc, DAT_RD_ERR_STAT);
		dev_dbg(udc->dev, "Device error (0x%x)!\n", tmp);
	}

	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}