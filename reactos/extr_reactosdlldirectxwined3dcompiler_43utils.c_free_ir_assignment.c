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
struct hlsl_ir_assignment {int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_assignment*) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ir_assignment(struct hlsl_ir_assignment *assignment)
{
    free_instr(assignment->lhs);
    free_instr(assignment->rhs);
    d3dcompiler_free(assignment);
}