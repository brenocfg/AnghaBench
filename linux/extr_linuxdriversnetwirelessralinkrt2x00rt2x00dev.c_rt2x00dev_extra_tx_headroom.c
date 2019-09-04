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
struct rt2x00_dev {TYPE_1__* tx; } ;
struct TYPE_2__ {unsigned int winfo_size; unsigned int desc_size; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 

__attribute__((used)) static unsigned int rt2x00dev_extra_tx_headroom(struct rt2x00_dev *rt2x00dev)
{
	if (WARN_ON(!rt2x00dev->tx))
		return 0;

	if (rt2x00_is_usb(rt2x00dev))
		return rt2x00dev->tx[0].winfo_size + rt2x00dev->tx[0].desc_size;

	return rt2x00dev->tx[0].winfo_size;
}