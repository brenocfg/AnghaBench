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
struct sctp_chunk {int /*<<< orphan*/  skb; int /*<<< orphan*/  chunk_end; TYPE_1__* chunk_hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int SCTP_PAD4 (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 void* skb_put_data (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  skb_put_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (int /*<<< orphan*/ ) ; 

void *sctp_addto_chunk(struct sctp_chunk *chunk, int len, const void *data)
{
	int chunklen = ntohs(chunk->chunk_hdr->length);
	int padlen = SCTP_PAD4(chunklen) - chunklen;
	void *target;

	skb_put_zero(chunk->skb, padlen);
	target = skb_put_data(chunk->skb, data, len);

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length = htons(chunklen + padlen + len);
	chunk->chunk_end = skb_tail_pointer(chunk->skb);

	return target;
}