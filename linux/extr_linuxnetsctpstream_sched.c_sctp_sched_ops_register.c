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
struct sctp_sched_ops {int dummy; } ;
typedef  enum sctp_sched_type { ____Placeholder_sctp_sched_type } sctp_sched_type ;

/* Variables and functions */
 struct sctp_sched_ops** sctp_sched_ops ; 

void sctp_sched_ops_register(enum sctp_sched_type sched,
			     struct sctp_sched_ops *sched_ops)
{
	sctp_sched_ops[sched] = sched_ops;
}