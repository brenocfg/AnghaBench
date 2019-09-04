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
struct tlv_desc {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_SET_LEN (struct tlv_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLV_SET_TYPE (struct tlv_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void tipc_tlv_init(struct sk_buff *skb, u16 type)
{
	struct tlv_desc *tlv = (struct tlv_desc *)skb->data;

	TLV_SET_LEN(tlv, 0);
	TLV_SET_TYPE(tlv, type);
	skb_put(skb, sizeof(struct tlv_desc));
}