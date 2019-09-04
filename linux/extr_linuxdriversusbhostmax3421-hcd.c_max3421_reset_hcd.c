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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct max3421_hcd {int mode; int hien; int /*<<< orphan*/  frame_number; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX3421_CPUCTL_IE_BIT ; 
 int /*<<< orphan*/  MAX3421_HCTL_FRMRST_BIT ; 
 int /*<<< orphan*/  MAX3421_HCTL_SAMPLEBUS_BIT ; 
 int /*<<< orphan*/  MAX3421_HI_BUSEVENT_BIT ; 
 int /*<<< orphan*/  MAX3421_HI_CONDET_BIT ; 
 int /*<<< orphan*/  MAX3421_HI_FRAME_BIT ; 
 int /*<<< orphan*/  MAX3421_MODE_DMPULLDN_BIT ; 
 int /*<<< orphan*/  MAX3421_MODE_DPPULLDN_BIT ; 
 int /*<<< orphan*/  MAX3421_MODE_HOST_BIT ; 
 int /*<<< orphan*/  MAX3421_MODE_SOFKAENAB_BIT ; 
 int /*<<< orphan*/  MAX3421_REG_CPUCTL ; 
 int /*<<< orphan*/  MAX3421_REG_HCTL ; 
 int /*<<< orphan*/  MAX3421_REG_HIEN ; 
 int /*<<< orphan*/  MAX3421_REG_MODE ; 
 int /*<<< orphan*/  MAX3421_REG_USBCTL ; 
 int /*<<< orphan*/  MAX3421_REG_USBIRQ ; 
 int /*<<< orphan*/  MAX3421_USBCTL_CHIPRES_BIT ; 
 int /*<<< orphan*/  MAX3421_USBIRQ_OSCOKIRQ_BIT ; 
 int /*<<< orphan*/  USB_MAX_FRAME_NUMBER ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  max3421_detect_conn (struct usb_hcd*) ; 
 int spi_rd8 (struct usb_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_wr8 (struct usb_hcd*,int /*<<< orphan*/ ,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
max3421_reset_hcd(struct usb_hcd *hcd)
{
	struct spi_device *spi = to_spi_device(hcd->self.controller);
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	int timeout;

	/* perform a chip reset and wait for OSCIRQ signal to appear: */
	spi_wr8(hcd, MAX3421_REG_USBCTL, BIT(MAX3421_USBCTL_CHIPRES_BIT));
	/* clear reset: */
	spi_wr8(hcd, MAX3421_REG_USBCTL, 0);
	timeout = 1000;
	while (1) {
		if (spi_rd8(hcd, MAX3421_REG_USBIRQ)
		    & BIT(MAX3421_USBIRQ_OSCOKIRQ_BIT))
			break;
		if (--timeout < 0) {
			dev_err(&spi->dev,
				"timed out waiting for oscillator OK signal");
			return 1;
		}
		cond_resched();
	}

	/*
	 * Turn on host mode, automatic generation of SOF packets, and
	 * enable pull-down registers on DM/DP:
	 */
	max3421_hcd->mode = (BIT(MAX3421_MODE_HOST_BIT) |
			     BIT(MAX3421_MODE_SOFKAENAB_BIT) |
			     BIT(MAX3421_MODE_DMPULLDN_BIT) |
			     BIT(MAX3421_MODE_DPPULLDN_BIT));
	spi_wr8(hcd, MAX3421_REG_MODE, max3421_hcd->mode);

	/* reset frame-number: */
	max3421_hcd->frame_number = USB_MAX_FRAME_NUMBER;
	spi_wr8(hcd, MAX3421_REG_HCTL, BIT(MAX3421_HCTL_FRMRST_BIT));

	/* sample the state of the D+ and D- lines */
	spi_wr8(hcd, MAX3421_REG_HCTL, BIT(MAX3421_HCTL_SAMPLEBUS_BIT));
	max3421_detect_conn(hcd);

	/* enable frame, connection-detected, and bus-event interrupts: */
	max3421_hcd->hien = (BIT(MAX3421_HI_FRAME_BIT) |
			     BIT(MAX3421_HI_CONDET_BIT) |
			     BIT(MAX3421_HI_BUSEVENT_BIT));
	spi_wr8(hcd, MAX3421_REG_HIEN, max3421_hcd->hien);

	/* enable interrupts: */
	spi_wr8(hcd, MAX3421_REG_CPUCTL, BIT(MAX3421_CPUCTL_IE_BIT));
	return 1;
}