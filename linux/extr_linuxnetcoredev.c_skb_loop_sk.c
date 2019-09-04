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
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; } ;
struct packet_type {int (* id_match ) (struct packet_type*,struct sock*) ;scalar_t__ af_packet_priv; } ;

/* Variables and functions */
 int stub1 (struct packet_type*,struct sock*) ; 

__attribute__((used)) static inline bool skb_loop_sk(struct packet_type *ptype, struct sk_buff *skb)
{
	if (!ptype->af_packet_priv || !skb->sk)
		return false;

	if (ptype->id_match)
		return ptype->id_match(ptype, skb->sk);
	else if ((struct sock *)ptype->af_packet_priv == skb->sk)
		return true;

	return false;
}