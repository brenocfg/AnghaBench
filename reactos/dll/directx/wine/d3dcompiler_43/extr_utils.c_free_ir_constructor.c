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
struct hlsl_ir_constructor {unsigned int args_count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_constructor*) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ir_constructor(struct hlsl_ir_constructor *constructor)
{
    unsigned int i;
    for (i = 0; i < constructor->args_count; ++i)
        free_instr(constructor->args[i]);
    d3dcompiler_free(constructor);
}