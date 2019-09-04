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
struct dpaa2_eth_priv {unsigned int rx_buf_align; } ;

/* Variables and functions */
 unsigned int DPAA2_ETH_SKB_SIZE ; 

__attribute__((used)) static inline unsigned int dpaa2_eth_buf_raw_size(struct dpaa2_eth_priv *priv)
{
	return DPAA2_ETH_SKB_SIZE + priv->rx_buf_align;
}