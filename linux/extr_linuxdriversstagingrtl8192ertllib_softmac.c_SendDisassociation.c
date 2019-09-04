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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct rtllib_network {int dummy; } ;
struct rtllib_device {struct rtllib_network current_network; } ;

/* Variables and functions */
 struct sk_buff* rtllib_disassociate_skb (struct rtllib_network*,struct rtllib_device*,int /*<<< orphan*/ ) ; 
 struct sk_buff* rtllib_disauth_skb (struct rtllib_network*,struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct rtllib_device*) ; 

void SendDisassociation(struct rtllib_device *ieee, bool deauth, u16 asRsn)
{
	struct rtllib_network *beacon = &ieee->current_network;
	struct sk_buff *skb;

	if (deauth)
		skb = rtllib_disauth_skb(beacon, ieee, asRsn);
	else
		skb = rtllib_disassociate_skb(beacon, ieee, asRsn);

	if (skb)
		softmac_mgmt_xmit(skb, ieee);
}