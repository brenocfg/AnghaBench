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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_usbdev {scalar_t__ write_fail; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int rsi_usb_card_write (struct rsi_hw*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rsi_write_multiple(struct rsi_hw *adapter,
			      u8 endpoint,
			      u8 *data,
			      u32 count)
{
	struct rsi_91x_usbdev *dev;

	if (!adapter)
		return -ENODEV;

	if (endpoint == 0)
		return -EINVAL;

	dev = (struct rsi_91x_usbdev *)adapter->rsi_dev;
	if (dev->write_fail)
		return -ENETDOWN;

	return rsi_usb_card_write(adapter, data, count, endpoint);
}