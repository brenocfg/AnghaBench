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
struct sctp_chunk {scalar_t__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_chunk_put (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_datamsg_put (scalar_t__) ; 

void sctp_chunk_free(struct sctp_chunk *chunk)
{
	/* Release our reference on the message tracker. */
	if (chunk->msg)
		sctp_datamsg_put(chunk->msg);

	sctp_chunk_put(chunk);
}