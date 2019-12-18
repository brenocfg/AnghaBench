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
struct sctp_association {int /*<<< orphan*/  unack_data; int /*<<< orphan*/  next_tsn; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__u32 sctp_association_get_next_tsn(struct sctp_association *asoc)
{
	/* From Section 1.6 Serial Number Arithmetic:
	 * Transmission Sequence Numbers wrap around when they reach
	 * 2**32 - 1.  That is, the next TSN a DATA chunk MUST use
	 * after transmitting TSN = 2*32 - 1 is TSN = 0.
	 */
	__u32 retval = asoc->next_tsn;
	asoc->next_tsn++;
	asoc->unack_data++;

	return retval;
}