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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_chunk {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union sctp_addr*,int) ; 

void sctp_init_addrs(struct sctp_chunk *chunk, union sctp_addr *src,
		     union sctp_addr *dest)
{
	memcpy(&chunk->source, src, sizeof(union sctp_addr));
	memcpy(&chunk->dest, dest, sizeof(union sctp_addr));
}