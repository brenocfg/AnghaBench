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
struct sk_buff {int len; int* data; } ;
struct TYPE_2__ {scalar_t__ pgn; } ;
struct j1939_sk_buff_cb {TYPE_1__ addr; } ;

/* Variables and functions */
 int J1939_PGN_ADDRESS_CLAIMED ; 
 scalar_t__ J1939_PGN_REQUEST ; 
 struct j1939_sk_buff_cb* j1939_skb_to_cb (struct sk_buff*) ; 

__attribute__((used)) static inline bool j1939_ac_msg_is_request(struct sk_buff *skb)
{
	struct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	int req_pgn;

	if (skb->len < 3 || skcb->addr.pgn != J1939_PGN_REQUEST)
		return false;

	req_pgn = skb->data[0] | (skb->data[1] << 8) | (skb->data[2] << 16);

	return req_pgn == J1939_PGN_ADDRESS_CLAIMED;
}