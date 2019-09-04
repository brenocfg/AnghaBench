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
typedef  int uint32_t ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct usb_cdc_speed_change {int /*<<< orphan*/  ULBitRate; int /*<<< orphan*/  DLBitRRate; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_info (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
cdc_ncm_speed_change(struct usbnet *dev,
		     struct usb_cdc_speed_change *data)
{
	uint32_t rx_speed = le32_to_cpu(data->DLBitRRate);
	uint32_t tx_speed = le32_to_cpu(data->ULBitRate);

	/*
	 * Currently the USB-NET API does not support reporting the actual
	 * device speed. Do print it instead.
	 */
	if ((tx_speed > 1000000) && (rx_speed > 1000000)) {
		netif_info(dev, link, dev->net,
			   "%u mbit/s downlink %u mbit/s uplink\n",
			   (unsigned int)(rx_speed / 1000000U),
			   (unsigned int)(tx_speed / 1000000U));
	} else {
		netif_info(dev, link, dev->net,
			   "%u kbit/s downlink %u kbit/s uplink\n",
			   (unsigned int)(rx_speed / 1000U),
			   (unsigned int)(tx_speed / 1000U));
	}
}