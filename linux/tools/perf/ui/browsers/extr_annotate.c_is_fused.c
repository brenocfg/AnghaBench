#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* name; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_7__ {TYPE_1__ ins; } ;
struct TYPE_8__ {TYPE_2__ locked; } ;
struct disasm_line {TYPE_4__ ins; TYPE_3__ ops; } ;
struct annotate_browser {int /*<<< orphan*/  arch; } ;
struct TYPE_10__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 TYPE_5__ al ; 
 int ins__is_fused (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ ins__is_lock (TYPE_4__*) ; 
 struct disasm_line* list_prev_entry (struct disasm_line*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_fused(struct annotate_browser *ab, struct disasm_line *cursor)
{
	struct disasm_line *pos = list_prev_entry(cursor, al.node);
	const char *name;

	if (!pos)
		return false;

	if (ins__is_lock(&pos->ins))
		name = pos->ops.locked.ins.name;
	else
		name = pos->ins.name;

	if (!name || !cursor->ins.name)
		return false;

	return ins__is_fused(ab->arch, name, cursor->ins.name);
}