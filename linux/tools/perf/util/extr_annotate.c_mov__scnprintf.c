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
struct TYPE_4__ {int /*<<< orphan*/  raw; scalar_t__ name; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; scalar_t__ name; } ;
struct ins_operands {TYPE_2__ target; TYPE_1__ source; } ;
struct ins {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov__scnprintf(struct ins *ins, char *bf, size_t size,
			   struct ins_operands *ops, int max_ins_name)
{
	return scnprintf(bf, size, "%-*s %s,%s", max_ins_name, ins->name,
			 ops->source.name ?: ops->source.raw,
			 ops->target.name ?: ops->target.raw);
}