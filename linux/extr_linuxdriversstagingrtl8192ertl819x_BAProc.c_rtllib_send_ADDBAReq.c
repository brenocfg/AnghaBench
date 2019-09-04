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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;
struct ba_record {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_ADDBAREQ ; 
 int /*<<< orphan*/  COMP_DBG ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* rtllib_ADDBA (struct rtllib_device*,int /*<<< orphan*/ *,struct ba_record*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct rtllib_device*) ; 

__attribute__((used)) static void rtllib_send_ADDBAReq(struct rtllib_device *ieee, u8 *dst,
				 struct ba_record *pBA)
{
	struct sk_buff *skb;

	skb = rtllib_ADDBA(ieee, dst, pBA, 0, ACT_ADDBAREQ);

	if (skb) {
		RT_TRACE(COMP_DBG, "====>to send ADDBAREQ!!!!!\n");
		softmac_mgmt_xmit(skb, ieee);
	} else {
		netdev_dbg(ieee->dev, "Failed to generate ADDBAReq packet.\n");
	}
}