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
struct Qdisc {int flags; int handle; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int TCQ_F_WARN_NONWC ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,int /*<<< orphan*/ ,int) ; 

void qdisc_warn_nonwc(const char *txt, struct Qdisc *qdisc)
{
	if (!(qdisc->flags & TCQ_F_WARN_NONWC)) {
		pr_warn("%s: %s qdisc %X: is non-work-conserving?\n",
			txt, qdisc->ops->id, qdisc->handle >> 16);
		qdisc->flags |= TCQ_F_WARN_NONWC;
	}
}