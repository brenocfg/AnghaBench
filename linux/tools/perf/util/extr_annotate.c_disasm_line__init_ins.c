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
struct map_symbol {int dummy; } ;
struct TYPE_3__ {TYPE_2__* ops; int /*<<< orphan*/  name; } ;
struct disasm_line {TYPE_1__ ins; int /*<<< orphan*/  ops; } ;
struct arch {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* parse ) (struct arch*,int /*<<< orphan*/ *,struct map_symbol*) ;} ;

/* Variables and functions */
 TYPE_2__* ins__find (struct arch*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct arch*,int /*<<< orphan*/ *,struct map_symbol*) ; 

__attribute__((used)) static void disasm_line__init_ins(struct disasm_line *dl, struct arch *arch, struct map_symbol *ms)
{
	dl->ins.ops = ins__find(arch, dl->ins.name);

	if (!dl->ins.ops)
		return;

	if (dl->ins.ops->parse && dl->ins.ops->parse(arch, &dl->ops, ms) < 0)
		dl->ins.ops = NULL;
}