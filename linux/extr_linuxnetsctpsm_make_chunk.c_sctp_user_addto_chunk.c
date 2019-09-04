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
struct iov_iter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  copy_from_iter_full (void*,int,struct iov_iter*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* skb_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (int /*<<< orphan*/ ) ; 

int sctp_user_addto_chunk(struct sctp_chunk *chunk, int len,
			  struct iov_iter *from)
{
	void *target;

	/* Make room in chunk for data.  */
	target = skb_put(chunk->skb, len);

	/* Copy data (whole iovec) into chunk */
	if (!copy_from_iter_full(target, len, from))
		return -EFAULT;

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length =
		htons(ntohs(chunk->chunk_hdr->length) + len);
	chunk->chunk_end = skb_tail_pointer(chunk->skb);

	return 0;
}