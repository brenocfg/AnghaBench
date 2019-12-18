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
struct d3dx_technique {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/ * D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_technique* get_technique_by_name (struct d3dx9_base_effect*,char const*) ; 
 int /*<<< orphan*/ * get_technique_handle (struct d3dx_technique*) ; 

__attribute__((used)) static D3DXHANDLE d3dx9_base_effect_get_technique_by_name(struct d3dx9_base_effect *base, const char *name)
{
    struct d3dx_technique *tech = get_technique_by_name(base, name);

    if (tech)
    {
        D3DXHANDLE t = get_technique_handle(tech);
        TRACE("Returning technique %p\n", t);
        return t;
    }

    WARN("Technique not found.\n");

    return NULL;
}