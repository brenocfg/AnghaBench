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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  raw; } ;
struct ins {TYPE_3__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  ops; struct ins ins; } ;
struct ins_operands {TYPE_1__ target; TYPE_2__ locked; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ins__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lock__delete(struct ins_operands *ops)
{
	struct ins *ins = &ops->locked.ins;

	if (ins->ops && ins->ops->free)
		ins->ops->free(ops->locked.ops);
	else
		ins__delete(ops->locked.ops);

	zfree(&ops->locked.ops);
	zfree(&ops->target.raw);
	zfree(&ops->target.name);
}