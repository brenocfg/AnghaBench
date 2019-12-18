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
struct dsmark_qdisc_data {struct Qdisc* q; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct dsmark_qdisc_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct Qdisc *dsmark_leaf(struct Qdisc *sch, unsigned long arg)
{
	struct dsmark_qdisc_data *p = qdisc_priv(sch);
	return p->q;
}