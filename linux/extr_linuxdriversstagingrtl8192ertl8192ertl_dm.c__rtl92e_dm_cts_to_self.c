#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt_hi_throughput {scalar_t__ IOTPeer; int /*<<< orphan*/  IOTAction; } ;
struct TYPE_4__ {unsigned long txbytesunicast; unsigned long rxbytesunicast; } ;
struct r8192_priv {TYPE_2__ stats; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int bCTSToSelfEnable; struct rt_hi_throughput* pHTInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_IOT_ACT_FORCED_CTS2SELF ; 
 scalar_t__ HT_IOT_PEER_BROADCOM ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_cts_to_self(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv((struct net_device *)dev);
	struct rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;
	static unsigned long lastTxOkCnt;
	static unsigned long lastRxOkCnt;
	unsigned long curTxOkCnt = 0;
	unsigned long curRxOkCnt = 0;

	if (priv->rtllib->bCTSToSelfEnable != true) {
		pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		return;
	}
	if (pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) {
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		if (curRxOkCnt > 4*curTxOkCnt)
			pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		else
			pHTInfo->IOTAction |= HT_IOT_ACT_FORCED_CTS2SELF;

		lastTxOkCnt = priv->stats.txbytesunicast;
		lastRxOkCnt = priv->stats.rxbytesunicast;
	}
}