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
struct dsmark_qdisc_data {TYPE_1__* mv; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int mask; scalar_t__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dsmark_valid_index (struct dsmark_qdisc_data*,unsigned long) ; 
 struct dsmark_qdisc_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int dsmark_delete(struct Qdisc *sch, unsigned long arg)
{
	struct dsmark_qdisc_data *p = qdisc_priv(sch);

	if (!dsmark_valid_index(p, arg))
		return -EINVAL;

	p->mv[arg - 1].mask = 0xff;
	p->mv[arg - 1].value = 0;

	return 0;
}