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
struct cas {int rx_fifo_size; int rx_pause_off; int rx_pause_on; TYPE_1__* dev; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 int ETH_HLEN ; 

__attribute__((used)) static void cas_init_pause_thresholds(struct cas *cp)
{
	/* Calculate pause thresholds.  Setting the OFF threshold to the
	 * full RX fifo size effectively disables PAUSE generation
	 */
	if (cp->rx_fifo_size <= (2 * 1024)) {
		cp->rx_pause_off = cp->rx_pause_on = cp->rx_fifo_size;
	} else {
		int max_frame = (cp->dev->mtu + ETH_HLEN + 4 + 4 + 64) & ~63;
		if (max_frame * 3 > cp->rx_fifo_size) {
			cp->rx_pause_off = 7104;
			cp->rx_pause_on  = 960;
		} else {
			int off = (cp->rx_fifo_size - (max_frame * 2));
			int on = off - max_frame;
			cp->rx_pause_off = off;
			cp->rx_pause_on = on;
		}
	}
}