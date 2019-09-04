#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_4__* chan; } ;
struct ieee80211_conf {int flags; scalar_t__ power_level; int /*<<< orphan*/  long_frame_max_tx_count; int /*<<< orphan*/  short_frame_max_tx_count; TYPE_1__ chandef; int /*<<< orphan*/  listen_interval; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;
struct b43_phy {scalar_t__ desired_txpower; scalar_t__ radio_on; TYPE_2__* ops; int /*<<< orphan*/  channel; TYPE_1__* chandef; } ;
struct b43_wldev {TYPE_3__* wl; int /*<<< orphan*/  radio_hw_enable; struct b43_phy phy; } ;
struct b43_wl {scalar_t__ radio_enabled; int /*<<< orphan*/  mutex; struct b43_wldev* current_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_7__ {int radiotap_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_rx_antenna ) (struct b43_wldev*,int) ;} ;

/* Variables and functions */
 int B43_ANTENNA_DEFAULT ; 
 int B43_TXPWR_IGNORE_TIME ; 
 int B43_TXPWR_IGNORE_TSSI ; 
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_LISTEN_INTERVAL ; 
 int IEEE80211_CONF_CHANGE_RETRY_LIMITS ; 
 int IEEE80211_CONF_MONITOR ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mgmtframe_txantenna (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_txpower_check (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_set_beacon_listen_interval (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_set_retry_limits (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_software_rfkill (struct b43_wldev*,int) ; 
 int b43_switch_band (struct b43_wldev*,TYPE_4__*) ; 
 int /*<<< orphan*/  b43_switch_channel (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43info (TYPE_3__*,char*) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*,int) ; 

__attribute__((used)) static int b43_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev = wl->current_dev;
	struct b43_phy *phy = &dev->phy;
	struct ieee80211_conf *conf = &hw->conf;
	int antenna;
	int err = 0;

	mutex_lock(&wl->mutex);
	b43_mac_suspend(dev);

	if (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL)
		b43_set_beacon_listen_interval(dev, conf->listen_interval);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		phy->chandef = &conf->chandef;
		phy->channel = conf->chandef.chan->hw_value;

		/* Switch the band (if necessary). */
		err = b43_switch_band(dev, conf->chandef.chan);
		if (err)
			goto out_mac_enable;

		/* Switch to the requested channel.
		 * The firmware takes care of races with the TX handler.
		 */
		b43_switch_channel(dev, phy->channel);
	}

	if (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		b43_set_retry_limits(dev, conf->short_frame_max_tx_count,
					  conf->long_frame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_RETRY_LIMITS;
	if (!changed)
		goto out_mac_enable;

	dev->wl->radiotap_enabled = !!(conf->flags & IEEE80211_CONF_MONITOR);

	/* Adjust the desired TX power level. */
	if (conf->power_level != 0) {
		if (conf->power_level != phy->desired_txpower) {
			phy->desired_txpower = conf->power_level;
			b43_phy_txpower_check(dev, B43_TXPWR_IGNORE_TIME |
						   B43_TXPWR_IGNORE_TSSI);
		}
	}

	/* Antennas for RX and management frame TX. */
	antenna = B43_ANTENNA_DEFAULT;
	b43_mgmtframe_txantenna(dev, antenna);
	antenna = B43_ANTENNA_DEFAULT;
	if (phy->ops->set_rx_antenna)
		phy->ops->set_rx_antenna(dev, antenna);

	if (wl->radio_enabled != phy->radio_on) {
		if (wl->radio_enabled) {
			b43_software_rfkill(dev, false);
			b43info(dev->wl, "Radio turned on by software\n");
			if (!dev->radio_hw_enable) {
				b43info(dev->wl, "The hardware RF-kill button "
					"still turns the radio physically off. "
					"Press the button to turn it on.\n");
			}
		} else {
			b43_software_rfkill(dev, true);
			b43info(dev->wl, "Radio turned off by software\n");
		}
	}

out_mac_enable:
	b43_mac_enable(dev);
	mutex_unlock(&wl->mutex);

	return err;
}