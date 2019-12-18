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
struct sctp_chunk {int pdiscard; TYPE_1__* chunk_hdr; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool sctp_chunk_length_valid(struct sctp_chunk *chunk,
					   __u16 required_length)
{
	__u16 chunk_length = ntohs(chunk->chunk_hdr->length);

	/* Previously already marked? */
	if (unlikely(chunk->pdiscard))
		return false;
	if (unlikely(chunk_length < required_length))
		return false;

	return true;
}