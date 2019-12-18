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
struct seq_file {int dummy; } ;
struct dyn_event {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* show ) (struct seq_file*,struct dyn_event*) ;} ;

/* Variables and functions */
 int stub1 (struct seq_file*,struct dyn_event*) ; 

__attribute__((used)) static int dyn_event_seq_show(struct seq_file *m, void *v)
{
	struct dyn_event *ev = v;

	if (ev && ev->ops)
		return ev->ops->show(m, ev);

	return 0;
}