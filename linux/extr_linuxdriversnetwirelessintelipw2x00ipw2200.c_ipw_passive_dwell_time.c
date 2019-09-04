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
struct ipw_priv {int status; TYPE_1__* assoc_network; } ;
struct TYPE_2__ {int beacon_interval; } ;

/* Variables and functions */
 int STATUS_ASSOCIATED ; 

__attribute__((used)) static int ipw_passive_dwell_time(struct ipw_priv *priv)
{
	/* staying on passive channels longer than the DTIM interval during a
	 * scan, while associated, causes the firmware to cancel the scan
	 * without notification. Hence, don't stay on passive channels longer
	 * than the beacon interval.
	 */
	if (priv->status & STATUS_ASSOCIATED
	    && priv->assoc_network->beacon_interval > 10)
		return priv->assoc_network->beacon_interval - 10;
	else
		return 120;
}