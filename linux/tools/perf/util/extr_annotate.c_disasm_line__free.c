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
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* ops; } ;
struct disasm_line {int /*<<< orphan*/  al; TYPE_2__ ins; int /*<<< orphan*/  ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  annotation_line__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ins__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void disasm_line__free(struct disasm_line *dl)
{
	if (dl->ins.ops && dl->ins.ops->free)
		dl->ins.ops->free(&dl->ops);
	else
		ins__delete(&dl->ops);
	zfree(&dl->ins.name);
	annotation_line__delete(&dl->al);
}