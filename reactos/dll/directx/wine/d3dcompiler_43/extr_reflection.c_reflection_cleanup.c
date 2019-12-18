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
struct d3dcompiler_shader_reflection {unsigned int constant_buffer_count; int /*<<< orphan*/ * creator; int /*<<< orphan*/ * resource_string; int /*<<< orphan*/ * bound_resources; int /*<<< orphan*/ * constant_buffers; int /*<<< orphan*/  types; int /*<<< orphan*/ * pcsg; int /*<<< orphan*/ * osgn; int /*<<< orphan*/ * isgn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dcompiler_shader_reflection*) ; 
 int /*<<< orphan*/  d3dcompiler_shader_reflection_type_destroy ; 
 int /*<<< orphan*/  free_constant_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_signature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_rb_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_cleanup(struct d3dcompiler_shader_reflection *ref)
{
    TRACE("Cleanup %p\n", ref);

    if (ref->isgn)
    {
        free_signature(ref->isgn);
        HeapFree(GetProcessHeap(), 0, ref->isgn);
    }

    if (ref->osgn)
    {
        free_signature(ref->osgn);
        HeapFree(GetProcessHeap(), 0, ref->osgn);
    }

    if (ref->pcsg)
    {
        free_signature(ref->pcsg);
        HeapFree(GetProcessHeap(), 0, ref->pcsg);
    }

    if (ref->constant_buffers)
    {
        unsigned int i;

        for (i = 0; i < ref->constant_buffer_count; ++i)
        {
            free_constant_buffer(&ref->constant_buffers[i]);
        }
    }

    wine_rb_destroy(&ref->types, d3dcompiler_shader_reflection_type_destroy, NULL);
    HeapFree(GetProcessHeap(), 0, ref->constant_buffers);
    HeapFree(GetProcessHeap(), 0, ref->bound_resources);
    HeapFree(GetProcessHeap(), 0, ref->resource_string);
    HeapFree(GetProcessHeap(), 0, ref->creator);
}