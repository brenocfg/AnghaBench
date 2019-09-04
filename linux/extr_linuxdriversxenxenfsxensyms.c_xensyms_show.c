#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenpf_symdata {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {struct xenpf_symdata symdata; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
struct xensyms {int /*<<< orphan*/  name; TYPE_2__ op; } ;
struct seq_file {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xensyms_show(struct seq_file *m, void *p)
{
	struct xensyms *xs = (struct xensyms *)m->private;
	struct xenpf_symdata *symdata = &xs->op.u.symdata;

	seq_printf(m, "%016llx %c %s\n", symdata->address,
		   symdata->type, xs->name);

	return 0;
}