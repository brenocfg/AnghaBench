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
struct d3dcompiler_shader_reflection_constant_buffer {unsigned int variable_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * variables; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_variable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_constant_buffer(struct d3dcompiler_shader_reflection_constant_buffer *cb)
{
    if (cb->variables)
    {
        unsigned int i;

        for (i = 0; i < cb->variable_count; ++i)
        {
            free_variable(&cb->variables[i]);
        }
        HeapFree(GetProcessHeap(), 0, cb->variables);
    }

    HeapFree(GetProcessHeap(), 0, cb->name);
}