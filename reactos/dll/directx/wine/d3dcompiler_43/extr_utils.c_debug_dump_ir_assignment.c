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
struct hlsl_ir_assignment {scalar_t__ writemask; int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;

/* Variables and functions */
 scalar_t__ BWRITERSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debug_dump_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_writemask (scalar_t__) ; 

__attribute__((used)) static void debug_dump_ir_assignment(const struct hlsl_ir_assignment *assign)
{
    TRACE("= (");
    debug_dump_instr(assign->lhs);
    if (assign->writemask != BWRITERSP_WRITEMASK_ALL)
        TRACE("%s", debug_writemask(assign->writemask));
    TRACE(" ");
    debug_dump_instr(assign->rhs);
    TRACE(")");
}