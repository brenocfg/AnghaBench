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
struct hfsc_class {scalar_t__ level; int /*<<< orphan*/  filter_cnt; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct hfsc_class* hfsc_find_class (int /*<<< orphan*/ ,struct Qdisc*) ; 

__attribute__((used)) static unsigned long
hfsc_bind_tcf(struct Qdisc *sch, unsigned long parent, u32 classid)
{
	struct hfsc_class *p = (struct hfsc_class *)parent;
	struct hfsc_class *cl = hfsc_find_class(classid, sch);

	if (cl != NULL) {
		if (p != NULL && p->level <= cl->level)
			return 0;
		cl->filter_cnt++;
	}

	return (unsigned long)cl;
}