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
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct TYPE_2__ {scalar_t__ buffer_full; } ;
struct rsi_91x_sdiodev {TYPE_1__ rx_info; } ;

/* Variables and functions */
 int EVENT_WAIT_FOREVER ; 

int rsi_sdio_determine_event_timeout(struct rsi_hw *adapter)
{
	struct rsi_91x_sdiodev *dev =
		(struct rsi_91x_sdiodev *)adapter->rsi_dev;

	/* Once buffer full is seen, event timeout to occur every 2 msecs */
	if (dev->rx_info.buffer_full)
		return 2;

	return EVENT_WAIT_FOREVER;
}