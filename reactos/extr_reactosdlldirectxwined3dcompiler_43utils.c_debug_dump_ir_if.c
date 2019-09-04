#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hlsl_ir_if {scalar_t__ else_instrs; scalar_t__ then_instrs; int /*<<< orphan*/  condition; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debug_dump_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_instr_list (scalar_t__) ; 

__attribute__((used)) static void debug_dump_ir_if(const struct hlsl_ir_if *if_node)
{
    TRACE("if (");
    debug_dump_instr(if_node->condition);
    TRACE(")\n{\n");
    debug_dump_instr_list(if_node->then_instrs);
    TRACE("}\n");
    if (if_node->else_instrs)
    {
        TRACE("else\n{\n");
        debug_dump_instr_list(if_node->else_instrs);
        TRACE("}\n");
    }
}