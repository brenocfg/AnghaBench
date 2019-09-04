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
typedef  int /*<<< orphan*/  u32 ;
struct cbq_sched_data {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ cbq_class_lookup (struct cbq_sched_data*,int /*<<< orphan*/ ) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static unsigned long cbq_find(struct Qdisc *sch, u32 classid)
{
	struct cbq_sched_data *q = qdisc_priv(sch);

	return (unsigned long)cbq_class_lookup(q, classid);
}