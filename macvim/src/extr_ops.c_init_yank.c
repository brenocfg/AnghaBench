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
struct TYPE_2__ {int /*<<< orphan*/ * y_array; } ;

/* Variables and functions */
 int NUM_REGISTERS ; 
 TYPE_1__* y_regs ; 

void
init_yank()
{
    int		i;

    for (i = 0; i < NUM_REGISTERS; ++i)
	y_regs[i].y_array = NULL;
}