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
struct drr_class {struct Qdisc* qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct Qdisc *drr_class_leaf(struct Qdisc *sch, unsigned long arg)
{
	struct drr_class *cl = (struct drr_class *)arg;

	return cl->qdisc;
}