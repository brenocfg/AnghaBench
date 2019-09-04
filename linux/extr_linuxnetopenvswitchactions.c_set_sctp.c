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
struct TYPE_2__ {void* dst; void* src; } ;
struct sw_flow_key {TYPE_1__ tp; } ;
struct sk_buff {int dummy; } ;
struct sctphdr {int checksum; void* dest; void* source; } ;
struct ovs_key_sctp {int /*<<< orphan*/  sctp_dst; int /*<<< orphan*/  sctp_src; } ;
typedef  int __le32 ;

/* Variables and functions */
 void* OVS_MASKED (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sctp_compute_cksum (struct sk_buff*,unsigned int) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_clear_hash (struct sk_buff*) ; 
 int skb_ensure_writable (struct sk_buff*,unsigned int) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_sctp(struct sk_buff *skb, struct sw_flow_key *flow_key,
		    const struct ovs_key_sctp *key,
		    const struct ovs_key_sctp *mask)
{
	unsigned int sctphoff = skb_transport_offset(skb);
	struct sctphdr *sh;
	__le32 old_correct_csum, new_csum, old_csum;
	int err;

	err = skb_ensure_writable(skb, sctphoff + sizeof(struct sctphdr));
	if (unlikely(err))
		return err;

	sh = sctp_hdr(skb);
	old_csum = sh->checksum;
	old_correct_csum = sctp_compute_cksum(skb, sctphoff);

	sh->source = OVS_MASKED(sh->source, key->sctp_src, mask->sctp_src);
	sh->dest = OVS_MASKED(sh->dest, key->sctp_dst, mask->sctp_dst);

	new_csum = sctp_compute_cksum(skb, sctphoff);

	/* Carry any checksum errors through. */
	sh->checksum = old_csum ^ old_correct_csum ^ new_csum;

	skb_clear_hash(skb);
	flow_key->tp.src = sh->source;
	flow_key->tp.dst = sh->dest;

	return 0;
}