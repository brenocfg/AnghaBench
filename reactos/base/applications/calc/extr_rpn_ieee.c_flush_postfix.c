#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ last_operator; scalar_t__ prev_operator; } ;

/* Variables and functions */
 TYPE_1__ calc ; 
 int /*<<< orphan*/  is_stack_empty () ; 
 int /*<<< orphan*/  pop () ; 

void flush_postfix(void)
{
    while (!is_stack_empty())
        pop();
    /* clear prev and last typed operators */
    calc.prev_operator =
    calc.last_operator = 0;
}