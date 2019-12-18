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
struct tcphdr {int /*<<< orphan*/  check; } ;
struct tcp_sack_block_wire {void* start_seq; void* end_seq; } ;
struct sk_buff {scalar_t__ data; } ;
struct nf_ct_seqadj {scalar_t__ offset_before; scalar_t__ offset_after; int /*<<< orphan*/  correction_pos; } ;
typedef  void* __be32 ;

/* Variables and functions */
 scalar_t__ after (scalar_t__,int /*<<< orphan*/ ) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,void*,void*,int) ; 
 scalar_t__ ntohl (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void nf_ct_sack_block_adjust(struct sk_buff *skb,
				    struct tcphdr *tcph,
				    unsigned int sackoff,
				    unsigned int sackend,
				    struct nf_ct_seqadj *seq)
{
	while (sackoff < sackend) {
		struct tcp_sack_block_wire *sack;
		__be32 new_start_seq, new_end_seq;

		sack = (void *)skb->data + sackoff;
		if (after(ntohl(sack->start_seq) - seq->offset_before,
			  seq->correction_pos))
			new_start_seq = htonl(ntohl(sack->start_seq) -
					seq->offset_after);
		else
			new_start_seq = htonl(ntohl(sack->start_seq) -
					seq->offset_before);

		if (after(ntohl(sack->end_seq) - seq->offset_before,
			  seq->correction_pos))
			new_end_seq = htonl(ntohl(sack->end_seq) -
				      seq->offset_after);
		else
			new_end_seq = htonl(ntohl(sack->end_seq) -
				      seq->offset_before);

		pr_debug("sack_adjust: start_seq: %u->%u, end_seq: %u->%u\n",
			 ntohl(sack->start_seq), ntohl(new_start_seq),
			 ntohl(sack->end_seq), ntohl(new_end_seq));

		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->start_seq, new_start_seq, false);
		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->end_seq, new_end_seq, false);
		sack->start_seq = new_start_seq;
		sack->end_seq = new_end_seq;
		sackoff += sizeof(*sack);
	}
}