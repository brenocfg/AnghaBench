#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sts; } ;
struct TYPE_6__ {int nparticipants; TYPE_1__* participants; } ;
struct TYPE_5__ {scalar_t__ read_page; } ;
typedef  TYPE_3__ SharedTuplestoreAccessor ;

/* Variables and functions */

void
sts_reinitialize(SharedTuplestoreAccessor *accessor)
{
	int			i;

	/*
	 * Reset the shared read head for all participants' files.  Also set the
	 * initial chunk size to the minimum (any increases from that size will be
	 * recorded in chunk_expansion_log).
	 */
	for (i = 0; i < accessor->sts->nparticipants; ++i)
	{
		accessor->sts->participants[i].read_page = 0;
	}
}