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
struct choke_sched_data {int /*<<< orphan*/  tab; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  choke_free (int /*<<< orphan*/ ) ; 
 struct choke_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void choke_destroy(struct Qdisc *sch)
{
	struct choke_sched_data *q = qdisc_priv(sch);

	choke_free(q->tab);
}