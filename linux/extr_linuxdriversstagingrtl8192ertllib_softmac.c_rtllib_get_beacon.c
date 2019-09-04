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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_ctl; } ;
struct rtllib_probe_response {TYPE_1__ header; } ;
struct rtllib_device {int* seq_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* rtllib_get_beacon_ (struct rtllib_device*) ; 

struct sk_buff *rtllib_get_beacon(struct rtllib_device *ieee)
{
	struct sk_buff *skb;
	struct rtllib_probe_response *b;

	skb = rtllib_get_beacon_(ieee);
	if (!skb)
		return NULL;

	b = (struct rtllib_probe_response *) skb->data;
	b->header.seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

	if (ieee->seq_ctrl[0] == 0xFFF)
		ieee->seq_ctrl[0] = 0;
	else
		ieee->seq_ctrl[0]++;

	return skb;
}