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
struct d3dx_technique {unsigned int pass_count; struct d3dx_pass* passes; } ;
struct d3dx_pass {unsigned int state_count; int /*<<< orphan*/ * states; } ;
struct d3dx_parameter {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_same_parameter ; 
 scalar_t__ walk_state_dep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct d3dx_parameter*) ; 

__attribute__((used)) static BOOL is_parameter_used(struct d3dx_parameter *param, struct d3dx_technique *tech)
{
    unsigned int i, j;
    struct d3dx_pass *pass;

    if (!tech || !param)
        return FALSE;

    for (i = 0; i < tech->pass_count; ++i)
    {
        pass = &tech->passes[i];
        for (j = 0; j < pass->state_count; ++j)
        {
            if (walk_state_dep(&pass->states[j], is_same_parameter, param))
                return TRUE;
        }
    }
    return FALSE;
}