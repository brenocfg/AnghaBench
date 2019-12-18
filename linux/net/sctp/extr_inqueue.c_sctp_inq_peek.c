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
struct sctp_inq {struct sctp_chunk* in_progress; } ;
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {scalar_t__ chunk_end; scalar_t__ pdiscard; scalar_t__ end_of_packet; scalar_t__ singleton; } ;

/* Variables and functions */

struct sctp_chunkhdr *sctp_inq_peek(struct sctp_inq *queue)
{
	struct sctp_chunk *chunk;
	struct sctp_chunkhdr *ch = NULL;

	chunk = queue->in_progress;
	/* If there is no more chunks in this packet, say so */
	if (chunk->singleton ||
	    chunk->end_of_packet ||
	    chunk->pdiscard)
		    return NULL;

	ch = (struct sctp_chunkhdr *)chunk->chunk_end;

	return ch;
}