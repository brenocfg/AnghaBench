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
struct d3dx_const_param_eval_output {scalar_t__ table; int register_index; } ;

/* Variables and functions */

__attribute__((used)) static int compare_const_set(const void *a, const void *b)
{
    const struct d3dx_const_param_eval_output *r1 = a;
    const struct d3dx_const_param_eval_output *r2 = b;

    if (r1->table != r2->table)
        return r1->table - r2->table;
    return r1->register_index - r2->register_index;
}