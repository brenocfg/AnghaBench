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
typedef  int u32 ;
struct rtl8169_private {int /*<<< orphan*/  cp_cmd; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int AcceptErr ; 
 int AcceptRunt ; 
 int /*<<< orphan*/  CPlusCmd ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RxChkSum ; 
 int /*<<< orphan*/  RxConfig ; 
 int /*<<< orphan*/  RxVlan ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_set_features(struct net_device *dev,
				netdev_features_t features)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	u32 rx_config;

	rtl_lock_work(tp);

	rx_config = RTL_R32(tp, RxConfig);
	if (features & NETIF_F_RXALL)
		rx_config |= (AcceptErr | AcceptRunt);
	else
		rx_config &= ~(AcceptErr | AcceptRunt);

	RTL_W32(tp, RxConfig, rx_config);

	if (features & NETIF_F_RXCSUM)
		tp->cp_cmd |= RxChkSum;
	else
		tp->cp_cmd &= ~RxChkSum;

	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		tp->cp_cmd |= RxVlan;
	else
		tp->cp_cmd &= ~RxVlan;

	RTL_W16(tp, CPlusCmd, tp->cp_cmd);
	RTL_R16(tp, CPlusCmd);

	rtl_unlock_work(tp);

	return 0;
}