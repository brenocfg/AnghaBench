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
struct d3dx_const_tab {unsigned int input_count; int /*<<< orphan*/ * inputs_param; int /*<<< orphan*/  update_version; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ULONG64_MAX ; 
 scalar_t__ is_top_level_param_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  top_level_parameter_from_parameter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL is_const_tab_input_dirty(struct d3dx_const_tab *ctab, ULONG64 update_version)
{
    unsigned int i;

    if (update_version == ULONG64_MAX)
        update_version = ctab->update_version;
    for (i = 0; i < ctab->input_count; ++i)
    {
        if (is_top_level_param_dirty(top_level_parameter_from_parameter(ctab->inputs_param[i]),
                update_version))
            return TRUE;
    }
    return FALSE;
}