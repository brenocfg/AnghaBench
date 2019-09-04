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
typedef  int /*<<< orphan*/  u8 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_RSSI ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_send_rssi_to_fw(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	rtl92e_writeb(dev, DRIVER_RSSI, (u8)priv->undecorated_smoothed_pwdb);
}