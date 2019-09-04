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
struct TYPE_2__ {int qhead; } ;
struct ks_wlan_private {TYPE_1__ tx_dev; } ;

/* Variables and functions */
 int TX_DEVICE_BUFF_SIZE ; 

__attribute__((used)) static inline void inc_txqhead(struct ks_wlan_private *priv)
{
	priv->tx_dev.qhead = (priv->tx_dev.qhead + 1) % TX_DEVICE_BUFF_SIZE;
}