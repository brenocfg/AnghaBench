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
struct i2400mu {int rx_size; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_printf (int,struct device*,char*,size_t,int) ; 

__attribute__((used)) static
size_t i2400mu_rx_size_grow(struct i2400mu *i2400mu)
{
	struct device *dev = &i2400mu->usb_iface->dev;
	size_t rx_size;
	const size_t max_pkt_size = 512;

	rx_size = 2 * i2400mu->rx_size;
	if (rx_size % max_pkt_size == 0) {
		rx_size -= 8;
		d_printf(1, dev,
			 "RX: expected size grew to %zu [adjusted -8] "
			 "from %zu\n",
			 rx_size, i2400mu->rx_size);
	} else
		d_printf(1, dev,
			 "RX: expected size grew to %zu from %zu\n",
			 rx_size, i2400mu->rx_size);
	return rx_size;
}