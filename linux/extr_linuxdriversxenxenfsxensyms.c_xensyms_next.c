#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ symnum; } ;
struct TYPE_5__ {TYPE_1__ symdata; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct xensyms {TYPE_3__ op; } ;
struct seq_file {scalar_t__ private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ xensyms_next_sym (struct xensyms*) ; 

__attribute__((used)) static void *xensyms_next(struct seq_file *m, void *p, loff_t *pos)
{
	struct xensyms *xs = (struct xensyms *)m->private;

	xs->op.u.symdata.symnum = ++(*pos);

	if (xensyms_next_sym(xs))
		return NULL;

	return p;
}