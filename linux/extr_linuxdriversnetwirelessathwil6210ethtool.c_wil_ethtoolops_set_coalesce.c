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
struct wireless_dev {scalar_t__ iftype; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* configure_interrupt_moderation ) (struct wil6210_priv*) ;} ;
struct wil6210_priv {TYPE_1__ txrx_ops; int /*<<< orphan*/  rx_max_burst_duration; int /*<<< orphan*/  tx_max_burst_duration; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  WIL6210_ITR_TRSH_MAX ; 
 struct wil6210_priv* ndev_to_wil (struct net_device*) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,struct ethtool_coalesce*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int wil_pm_runtime_get (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_pm_runtime_put (struct wil6210_priv*) ; 

__attribute__((used)) static int wil_ethtoolops_set_coalesce(struct net_device *ndev,
				       struct ethtool_coalesce *cp)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);
	struct wireless_dev *wdev = ndev->ieee80211_ptr;
	int ret;

	wil_dbg_misc(wil, "ethtoolops_set_coalesce: rx %d usec, tx %d usec\n",
		     cp->rx_coalesce_usecs, cp->tx_coalesce_usecs);

	if (wdev->iftype == NL80211_IFTYPE_MONITOR) {
		wil_dbg_misc(wil, "No IRQ coalescing in monitor mode\n");
		return -EINVAL;
	}

	/* only @rx_coalesce_usecs and @tx_coalesce_usecs supported,
	 * ignore other parameters
	 */

	if (cp->rx_coalesce_usecs > WIL6210_ITR_TRSH_MAX ||
	    cp->tx_coalesce_usecs > WIL6210_ITR_TRSH_MAX)
		goto out_bad;

	wil->tx_max_burst_duration = cp->tx_coalesce_usecs;
	wil->rx_max_burst_duration = cp->rx_coalesce_usecs;

	ret = wil_pm_runtime_get(wil);
	if (ret < 0)
		return ret;

	wil->txrx_ops.configure_interrupt_moderation(wil);

	wil_pm_runtime_put(wil);

	return 0;

out_bad:
	wil_dbg_misc(wil, "Unsupported coalescing params. Raw command:\n");
	print_hex_dump_debug("DBG[MISC] coal ", DUMP_PREFIX_OFFSET, 16, 4,
			     cp, sizeof(*cp), false);
	return -EINVAL;
}