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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct rtllib_hdr_3addr {int dummy; } ;
struct rtllib_hdr {int dummy; } ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ACT_ADDBAREQ 131 
#define  ACT_ADDBARSP 130 
#define  ACT_CAT_BA 129 
#define  ACT_DELBA 128 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int* rtllib_get_payload (struct rtllib_hdr*) ; 
 int /*<<< orphan*/  rtllib_rx_ADDBAReq (struct rtllib_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtllib_rx_ADDBARsp (struct rtllib_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtllib_rx_DELBA (struct rtllib_device*,struct sk_buff*) ; 

__attribute__((used)) static void rtllib_process_action(struct rtllib_device *ieee,
				  struct sk_buff *skb)
{
	struct rtllib_hdr_3addr *header = (struct rtllib_hdr_3addr *) skb->data;
	u8 *act = rtllib_get_payload((struct rtllib_hdr *)header);
	u8 category = 0;

	if (act == NULL) {
		netdev_warn(ieee->dev,
			    "Error getting payload of action frame\n");
		return;
	}

	category = *act;
	act++;
	switch (category) {
	case ACT_CAT_BA:
		switch (*act) {
		case ACT_ADDBAREQ:
			rtllib_rx_ADDBAReq(ieee, skb);
			break;
		case ACT_ADDBARSP:
			rtllib_rx_ADDBARsp(ieee, skb);
			break;
		case ACT_DELBA:
			rtllib_rx_DELBA(ieee, skb);
			break;
		}
		break;
	default:
		break;
	}
}