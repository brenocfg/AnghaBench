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
struct d3dx_parameter {scalar_t__ class; scalar_t__ type; scalar_t__ rows; scalar_t__ columns; scalar_t__ element_count; unsigned int member_count; struct d3dx_parameter* members; int /*<<< orphan*/  name; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL is_same_parameter(void *param1_, struct d3dx_parameter *param2)
{
    struct d3dx_parameter *param1 = (struct d3dx_parameter *)param1_;
    BOOL matches;
    unsigned int i, member_count;

    matches = !strcmp(param1->name, param2->name) && param1->class == param2->class
            && param1->type == param2->type && param1->rows == param2->rows
            && param1->columns == param2->columns && param1->element_count == param2->element_count
            && param1->member_count == param2->member_count;

    member_count = param1->element_count ? param1->element_count : param1->member_count;

    if (!matches || !member_count)
        return matches;

    for (i = 0; i < member_count; ++i)
    {
        if (!is_same_parameter(&param1->members[i], &param2->members[i]))
            return FALSE;
    }
    return TRUE;
}