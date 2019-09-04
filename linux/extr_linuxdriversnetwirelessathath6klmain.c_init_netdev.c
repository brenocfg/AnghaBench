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
struct wmi_data_hdr {int dummy; } ;
struct net_device {int needs_free_netdev; int hw_features; int /*<<< orphan*/  needed_headroom; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct ath6kl_llc_snap_hdr {int dummy; } ;
struct ath6kl {int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_NO_IP_CHECKSUM ; 
 scalar_t__ ATH6KL_HTC_ALIGN_BYTES ; 
 int /*<<< orphan*/  ATH6KL_TX_TIMEOUT ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ WMI_MAX_TX_META_SZ ; 
 int /*<<< orphan*/  ath6kl_netdev_ops ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_netdev(struct net_device *dev)
{
	struct ath6kl *ar = ath6kl_priv(dev);

	dev->netdev_ops = &ath6kl_netdev_ops;
	dev->needs_free_netdev = true;
	dev->watchdog_timeo = ATH6KL_TX_TIMEOUT;

	dev->needed_headroom = ETH_HLEN;
	dev->needed_headroom += roundup(sizeof(struct ath6kl_llc_snap_hdr) +
					sizeof(struct wmi_data_hdr) +
					HTC_HDR_LENGTH +
					WMI_MAX_TX_META_SZ +
					ATH6KL_HTC_ALIGN_BYTES, 4);

	if (!test_bit(ATH6KL_FW_CAPABILITY_NO_IP_CHECKSUM,
		      ar->fw_capabilities))
		dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

	return;
}