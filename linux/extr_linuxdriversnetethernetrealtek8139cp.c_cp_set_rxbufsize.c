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
struct cp_private {scalar_t__ rx_buf_sz; TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned int mtu; } ;

/* Variables and functions */
 unsigned int ETH_DATA_LEN ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ PKT_BUF_SZ ; 

__attribute__((used)) static inline void cp_set_rxbufsize (struct cp_private *cp)
{
	unsigned int mtu = cp->dev->mtu;

	if (mtu > ETH_DATA_LEN)
		/* MTU + ethernet header + FCS + optional VLAN tag */
		cp->rx_buf_sz = mtu + ETH_HLEN + 8;
	else
		cp->rx_buf_sz = PKT_BUF_SZ;
}