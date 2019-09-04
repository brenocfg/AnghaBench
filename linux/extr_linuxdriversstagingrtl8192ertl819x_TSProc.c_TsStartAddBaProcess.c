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
struct tx_ts_record {int bAddBaReqInProgress; int /*<<< orphan*/  TsAddBaTimer; scalar_t__ bAddBaReqDelayed; } ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_ADDBA_DELAY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 

void TsStartAddBaProcess(struct rtllib_device *ieee, struct tx_ts_record *pTxTS)
{
	if (pTxTS->bAddBaReqInProgress == false) {
		pTxTS->bAddBaReqInProgress = true;

		if (pTxTS->bAddBaReqDelayed) {
			netdev_dbg(ieee->dev, "Start ADDBA after 60 sec!!\n");
			mod_timer(&pTxTS->TsAddBaTimer, jiffies +
				  msecs_to_jiffies(TS_ADDBA_DELAY));
		} else {
			netdev_dbg(ieee->dev, "Immediately Start ADDBA\n");
			mod_timer(&pTxTS->TsAddBaTimer, jiffies+10);
		}
	} else
		netdev_dbg(ieee->dev, "BA timer is already added\n");
}