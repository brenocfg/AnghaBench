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
struct sctp_association {int need_ecne; int /*<<< orphan*/  last_ecne_tsn; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__attribute__((used)) static void sctp_do_ecn_ce_work(struct sctp_association *asoc,
				__u32 lowest_tsn)
{
	/* Save the TSN away for comparison when we receive CWR */

	asoc->last_ecne_tsn = lowest_tsn;
	asoc->need_ecne = 1;
}