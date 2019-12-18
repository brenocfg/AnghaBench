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

/* Variables and functions */
 int /*<<< orphan*/  SCTP_SS_PRIO ; 
 int /*<<< orphan*/  sctp_sched_ops_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sched_prio ; 

void sctp_sched_ops_prio_init(void)
{
	sctp_sched_ops_register(SCTP_SS_PRIO, &sctp_sched_prio);
}