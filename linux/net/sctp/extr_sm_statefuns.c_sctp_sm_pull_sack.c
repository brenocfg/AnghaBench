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
struct sctp_sackhdr {int /*<<< orphan*/  num_dup_tsns; int /*<<< orphan*/  num_gap_ack_blocks; } ;
struct sctp_chunk {TYPE_1__* skb; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;
struct TYPE_2__ {unsigned int len; scalar_t__ data; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static struct sctp_sackhdr *sctp_sm_pull_sack(struct sctp_chunk *chunk)
{
	struct sctp_sackhdr *sack;
	__u16 num_dup_tsns;
	unsigned int len;
	__u16 num_blocks;

	/* Protect ourselves from reading too far into
	 * the skb from a bogus sender.
	 */
	sack = (struct sctp_sackhdr *) chunk->skb->data;

	num_blocks = ntohs(sack->num_gap_ack_blocks);
	num_dup_tsns = ntohs(sack->num_dup_tsns);
	len = sizeof(struct sctp_sackhdr);
	len += (num_blocks + num_dup_tsns) * sizeof(__u32);
	if (len > chunk->skb->len)
		return NULL;

	skb_pull(chunk->skb, len);

	return sack;
}