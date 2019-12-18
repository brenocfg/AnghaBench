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
struct d3dx9_base_effect {unsigned int parameter_count; unsigned int technique_count; unsigned int object_count; int /*<<< orphan*/ * objects; int /*<<< orphan*/ * techniques; int /*<<< orphan*/ * parameters; int /*<<< orphan*/  full_name_tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dx9_base_effect*) ; 
 int /*<<< orphan*/  free_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_technique (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_top_level_parameter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3dx9_base_effect_cleanup(struct d3dx9_base_effect *base)
{
    unsigned int i;

    TRACE("base %p.\n", base);

    heap_free(base->full_name_tmp);

    if (base->parameters)
    {
        for (i = 0; i < base->parameter_count; ++i)
            free_top_level_parameter(&base->parameters[i]);
        HeapFree(GetProcessHeap(), 0, base->parameters);
        base->parameters = NULL;
    }

    if (base->techniques)
    {
        for (i = 0; i < base->technique_count; ++i)
            free_technique(&base->techniques[i]);
        HeapFree(GetProcessHeap(), 0, base->techniques);
        base->techniques = NULL;
    }

    if (base->objects)
    {
        for (i = 0; i < base->object_count; ++i)
        {
            free_object(&base->objects[i]);
        }
        HeapFree(GetProcessHeap(), 0, base->objects);
        base->objects = NULL;
    }
}