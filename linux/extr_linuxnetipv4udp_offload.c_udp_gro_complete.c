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
typedef  struct sock* (* udp_lookup_t ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  len; } ;
struct sock {int dummy; } ;
struct sk_buff {int encapsulation; scalar_t__ remcsum_offload; scalar_t__ data; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  gso_type; } ;
struct TYPE_3__ {int (* gro_complete ) (struct sock*,struct sk_buff*,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  SKB_GSO_TUNNEL_REMCSUM ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 struct sock* stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct sock*,struct sk_buff*,int) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

int udp_gro_complete(struct sk_buff *skb, int nhoff,
		     udp_lookup_t lookup)
{
	__be16 newlen = htons(skb->len - nhoff);
	struct udphdr *uh = (struct udphdr *)(skb->data + nhoff);
	int err = -ENOSYS;
	struct sock *sk;

	uh->len = newlen;

	/* Set encapsulation before calling into inner gro_complete() functions
	 * to make them set up the inner offsets.
	 */
	skb->encapsulation = 1;

	rcu_read_lock();
	sk = (*lookup)(skb, uh->source, uh->dest);
	if (sk && udp_sk(sk)->gro_complete)
		err = udp_sk(sk)->gro_complete(sk, skb,
				nhoff + sizeof(struct udphdr));
	rcu_read_unlock();

	if (skb->remcsum_offload)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TUNNEL_REMCSUM;

	return err;
}