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
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ops; } ;
struct disasm_line {TYPE_2__ ops; TYPE_1__ ins; } ;

/* Variables and functions */
 int ins__scnprintf (TYPE_1__*,char*,size_t,TYPE_2__*) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int disasm_line__scnprintf(struct disasm_line *dl, char *bf, size_t size, bool raw)
{
	if (raw || !dl->ins.ops)
		return scnprintf(bf, size, "%-6s %s", dl->ins.name, dl->ops.raw);

	return ins__scnprintf(&dl->ins, bf, size, &dl->ops);
}