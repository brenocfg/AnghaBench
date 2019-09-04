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
struct sis190_private {unsigned int rx_buf_sz; } ;
struct net_device {unsigned int mtu; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 int RX_BUF_MASK ; 
 unsigned int RX_BUF_SIZE ; 

__attribute__((used)) static void sis190_set_rxbufsize(struct sis190_private *tp,
				 struct net_device *dev)
{
	unsigned int mtu = dev->mtu;

	tp->rx_buf_sz = (mtu > RX_BUF_SIZE) ? mtu + ETH_HLEN + 8 : RX_BUF_SIZE;
	/* RxDesc->size has a licence to kill the lower bits */
	if (tp->rx_buf_sz & 0x07) {
		tp->rx_buf_sz += 8;
		tp->rx_buf_sz &= RX_BUF_MASK;
	}
}