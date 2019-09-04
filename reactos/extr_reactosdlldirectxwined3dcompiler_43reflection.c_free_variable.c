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
struct d3dcompiler_shader_reflection_variable {int /*<<< orphan*/  default_value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_variable(struct d3dcompiler_shader_reflection_variable *var)
{
    if (var)
    {
        HeapFree(GetProcessHeap(), 0, var->name);
        HeapFree(GetProcessHeap(), 0, var->default_value);
    }
}