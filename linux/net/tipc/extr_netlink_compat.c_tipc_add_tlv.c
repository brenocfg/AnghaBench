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
struct tlv_desc {void* tlv_len; void* tlv_type; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TLV_DATA (struct tlv_desc*) ; 
 int /*<<< orphan*/  TLV_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_SPACE (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ tipc_skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int tipc_add_tlv(struct sk_buff *skb, u16 type, void *data, u16 len)
{
	struct tlv_desc *tlv = (struct tlv_desc *)skb_tail_pointer(skb);

	if (tipc_skb_tailroom(skb) < TLV_SPACE(len))
		return -EMSGSIZE;

	skb_put(skb, TLV_SPACE(len));
	tlv->tlv_type = htons(type);
	tlv->tlv_len = htons(TLV_LENGTH(len));
	if (len && data)
		memcpy(TLV_DATA(tlv), data, len);

	return 0;
}