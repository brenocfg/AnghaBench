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
struct hlsl_ir_if {int /*<<< orphan*/  else_instrs; int /*<<< orphan*/  then_instrs; int /*<<< orphan*/  condition; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_if*) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_instr_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ir_if(struct hlsl_ir_if *if_node)
{
    free_instr(if_node->condition);
    free_instr_list(if_node->then_instrs);
    free_instr_list(if_node->else_instrs);
    d3dcompiler_free(if_node);
}