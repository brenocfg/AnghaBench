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
struct r8192_priv {int framesyncMonitor; int /*<<< orphan*/  fsync_timer; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int fsync_time_interval; int fsync_rate_bitmap; int fsync_rssi_threshold; int bfsync_enable; int fsync_multiple_timeinterval; int fsync_firstdiff_ratethreshold; int fsync_seconddiff_ratethreshold; int /*<<< orphan*/  fsync_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Default_Fsync ; 
 int /*<<< orphan*/  dm_fsync_timer_callback ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_init_fsync(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	priv->ieee80211->fsync_time_interval = 500;
	priv->ieee80211->fsync_rate_bitmap = 0x0f000800;
	priv->ieee80211->fsync_rssi_threshold = 30;
	priv->ieee80211->bfsync_enable = false;
	priv->ieee80211->fsync_multiple_timeinterval = 3;
	priv->ieee80211->fsync_firstdiff_ratethreshold = 100;
	priv->ieee80211->fsync_seconddiff_ratethreshold = 200;
	priv->ieee80211->fsync_state = Default_Fsync;
	priv->framesyncMonitor = 1;	/* current default 0xc38 monitor on */
	timer_setup(&priv->fsync_timer, dm_fsync_timer_callback, 0);
}