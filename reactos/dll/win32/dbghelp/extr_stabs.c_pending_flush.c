#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct symt_function {scalar_t__ address; } ;
struct symt_block {int dummy; } ;
struct pending_list {unsigned int num; TYPE_4__* objs; } ;
struct module {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  line_num; int /*<<< orphan*/  source_idx; scalar_t__ load_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  loc; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {TYPE_2__ line; TYPE_1__ var; } ;
struct TYPE_8__ {int tag; TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMT_MACHO ; 
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
#define  PENDING_LINE 129 
#define  PENDING_VAR 128 
 int /*<<< orphan*/  symt_add_func_line (struct module*,struct symt_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  symt_add_func_local (struct module*,struct symt_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct symt_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pending_flush(struct pending_list* pending, struct module* module,
                          struct symt_function* func, struct symt_block* block)
{
    unsigned int i;

    for (i = 0; i < pending->num; i++)
    {
        switch (pending->objs[i].tag)
        {
        case PENDING_VAR:
            symt_add_func_local(module, func,
                                pending->objs[i].u.var.kind, &pending->objs[i].u.var.loc,
                                block, pending->objs[i].u.var.type, pending->objs[i].u.var.name);
            break;
        case PENDING_LINE:
            if (module->type == DMT_MACHO)
                pending->objs[i].u.line.offset -= func->address - pending->objs[i].u.line.load_offset;
            symt_add_func_line(module, func, pending->objs[i].u.line.source_idx,
                               pending->objs[i].u.line.line_num, pending->objs[i].u.line.offset);
            break;
        default:
            ERR("Unknown pending object tag %u\n", (unsigned)pending->objs[i].tag);
            break;
        }
    }
    pending->num = 0;
}