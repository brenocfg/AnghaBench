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
struct TYPE_2__ {scalar_t__ sched; } ;
struct sctp_association {TYPE_1__ outqueue; } ;

/* Variables and functions */
 int SCTP_SS_MAX ; 
 scalar_t__* sctp_sched_ops ; 

int sctp_sched_get_sched(struct sctp_association *asoc)
{
	int i;

	for (i = 0; i <= SCTP_SS_MAX; i++)
		if (asoc->outqueue.sched == sctp_sched_ops[i])
			return i;

	return 0;
}