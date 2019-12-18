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
struct d3dx9_base_effect {size_t technique_count; int /*<<< orphan*/ * techniques; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/ * D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * get_technique_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_technique(struct d3dx9_base_effect *base, UINT index)
{
    if (index >= base->technique_count)
    {
        WARN("Invalid argument specified.\n");
        return NULL;
    }

    TRACE("Returning technique %p.\n", &base->techniques[index]);

    return get_technique_handle(&base->techniques[index]);
}