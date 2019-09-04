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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__* data; size_t len; } ;

/* Variables and functions */
 size_t LLCP_HEADER_SIZE ; 
 scalar_t__ LLCP_TLV_SN ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u8 *nfc_llcp_connect_sn(struct sk_buff *skb, size_t *sn_len)
{
	u8 *tlv = &skb->data[2], type, length;
	size_t tlv_array_len = skb->len - LLCP_HEADER_SIZE, offset = 0;

	while (offset < tlv_array_len) {
		type = tlv[0];
		length = tlv[1];

		pr_debug("type 0x%x length %d\n", type, length);

		if (type == LLCP_TLV_SN) {
			*sn_len = length;
			return &tlv[2];
		}

		offset += length + 2;
		tlv += length + 2;
	}

	return NULL;
}