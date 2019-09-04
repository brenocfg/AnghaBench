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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;
struct ba_record {int dummy; } ;
typedef  enum tr_select { ____Placeholder_tr_select } tr_select ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* rtllib_DELBA (struct rtllib_device*,int /*<<< orphan*/ *,struct ba_record*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct rtllib_device*) ; 

__attribute__((used)) static void rtllib_send_DELBA(struct rtllib_device *ieee, u8 *dst,
			      struct ba_record *pBA, enum tr_select TxRxSelect,
			      u16 ReasonCode)
{
	struct sk_buff *skb;

	skb = rtllib_DELBA(ieee, dst, pBA, TxRxSelect, ReasonCode);
	if (skb)
		softmac_mgmt_xmit(skb, ieee);
	else
		netdev_dbg(ieee->dev, "Failed to generate DELBA packet.\n");
}