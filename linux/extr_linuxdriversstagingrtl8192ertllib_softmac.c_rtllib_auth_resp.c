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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; } ;
struct rtllib_device {TYPE_1__* dev; int /*<<< orphan*/  tx_headroom; } ;
struct TYPE_4__ {void* frame_ctl; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; } ;
struct rtllib_authentication {TYPE_2__ header; void* algorithm; void* transaction; void* status; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int RTLLIB_STYPE_AUTH ; 
 int WLAN_AUTH_OPEN ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rtllib_authentication* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtllib_auth_resp(struct rtllib_device *ieee, int status,
				 u8 *dest)
{
	struct sk_buff *skb = NULL;
	struct rtllib_authentication *auth;
	int len = ieee->tx_headroom + sizeof(struct rtllib_authentication) + 1;

	skb = dev_alloc_skb(len);
	if (!skb)
		return NULL;

	skb->len = sizeof(struct rtllib_authentication);

	skb_reserve(skb, ieee->tx_headroom);

	auth = skb_put(skb, sizeof(struct rtllib_authentication));

	auth->status = cpu_to_le16(status);
	auth->transaction = cpu_to_le16(2);
	auth->algorithm = cpu_to_le16(WLAN_AUTH_OPEN);

	ether_addr_copy(auth->header.addr3, ieee->dev->dev_addr);
	ether_addr_copy(auth->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(auth->header.addr1, dest);
	auth->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_AUTH);
	return skb;


}