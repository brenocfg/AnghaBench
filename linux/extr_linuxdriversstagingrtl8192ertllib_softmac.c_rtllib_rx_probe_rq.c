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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_probe_rs; int /*<<< orphan*/  rx_probe_rq; } ;
struct rtllib_device {TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ probe_rq_parse (struct rtllib_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_resp_to_probe (struct rtllib_device*,int /*<<< orphan*/ *) ; 

void rtllib_rx_probe_rq(struct rtllib_device *ieee, struct sk_buff *skb)
{
	u8 dest[ETH_ALEN];

	ieee->softmac_stats.rx_probe_rq++;
	if (probe_rq_parse(ieee, skb, dest) > 0) {
		ieee->softmac_stats.tx_probe_rs++;
		rtllib_resp_to_probe(ieee, dest);
	}
}