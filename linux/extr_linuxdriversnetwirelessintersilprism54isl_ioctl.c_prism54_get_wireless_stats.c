#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ updated; } ;
struct iw_statistics {TYPE_2__ qual; } ;
struct TYPE_6__ {scalar_t__ updated; } ;
struct TYPE_9__ {TYPE_1__ qual; } ;
struct TYPE_8__ {scalar_t__ stats_timestamp; struct iw_statistics iwstatistics; int /*<<< orphan*/  stats_work; int /*<<< orphan*/  stats_lock; TYPE_5__ local_iwstatistics; } ;
typedef  TYPE_3__ islpci_private ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (struct iw_statistics*,TYPE_5__*,int) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

struct iw_statistics *
prism54_get_wireless_stats(struct net_device *ndev)
{
	islpci_private *priv = netdev_priv(ndev);

	/* If the stats are being updated return old data */
	if (mutex_trylock(&priv->stats_lock)) {
		memcpy(&priv->iwstatistics, &priv->local_iwstatistics,
		       sizeof (struct iw_statistics));
		/* They won't be marked updated for the next time */
		priv->local_iwstatistics.qual.updated = 0;
		mutex_unlock(&priv->stats_lock);
	} else
		priv->iwstatistics.qual.updated = 0;

	/* Update our wireless stats, but do not schedule to often
	 * (max 1 HZ) */
	if ((priv->stats_timestamp == 0) ||
	    time_after(jiffies, priv->stats_timestamp + 1 * HZ)) {
		schedule_work(&priv->stats_work);
		priv->stats_timestamp = jiffies;
	}

	return &priv->iwstatistics;
}