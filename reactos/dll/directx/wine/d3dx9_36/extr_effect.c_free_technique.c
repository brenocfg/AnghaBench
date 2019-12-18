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
struct d3dx_technique {unsigned int annotation_count; unsigned int pass_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * passes; int /*<<< orphan*/ * annotations; int /*<<< orphan*/ * saved_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DStateBlock9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dx_technique*) ; 
 int /*<<< orphan*/  free_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pass (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_technique(struct d3dx_technique *technique)
{
    unsigned int i;

    TRACE("Free technique %p\n", technique);

    if (!technique)
        return;

    if (technique->saved_state)
    {
        IDirect3DStateBlock9_Release(technique->saved_state);
        technique->saved_state = NULL;
    }

    if (technique->annotations)
    {
        for (i = 0; i < technique->annotation_count; ++i)
            free_parameter(&technique->annotations[i], FALSE, FALSE);
        HeapFree(GetProcessHeap(), 0, technique->annotations);
        technique->annotations = NULL;
    }

    if (technique->passes)
    {
        for (i = 0; i < technique->pass_count; ++i)
            free_pass(&technique->passes[i]);
        HeapFree(GetProcessHeap(), 0, technique->passes);
        technique->passes = NULL;
    }

    HeapFree(GetProcessHeap(), 0, technique->name);
    technique->name = NULL;
}