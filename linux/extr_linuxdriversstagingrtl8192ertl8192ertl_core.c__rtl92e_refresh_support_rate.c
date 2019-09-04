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
struct rtllib_device {scalar_t__ mode; int /*<<< orphan*/  Regdot11HTOperationalRateSet; int /*<<< orphan*/  RegHTSuppRateSet; int /*<<< orphan*/  Regdot11TxHTOperationalRateSet; } ;
struct r8192_priv {struct rtllib_device* rtllib; } ;

/* Variables and functions */
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92e_refresh_support_rate(struct r8192_priv *priv)
{
	struct rtllib_device *ieee = priv->rtllib;

	if (ieee->mode == WIRELESS_MODE_N_24G ||
	    ieee->mode == WIRELESS_MODE_N_5G) {
		memcpy(ieee->Regdot11HTOperationalRateSet,
		       ieee->RegHTSuppRateSet, 16);
		memcpy(ieee->Regdot11TxHTOperationalRateSet,
		       ieee->RegHTSuppRateSet, 16);

	} else {
		memset(ieee->Regdot11HTOperationalRateSet, 0, 16);
	}
}