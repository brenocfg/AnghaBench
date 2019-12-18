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
struct fall {scalar_t__ shape; } ;

/* Variables and functions */
 scalar_t__ SHAPE_MAX ; 
 int* block_sizes ; 
 struct fall const** fall ; 

__attribute__((constructor)) void calculate_block_sizes(void)
{
    for (int i = 0; i < 10; i++) {
        const struct fall *instr = fall[i];

        while (instr->shape != SHAPE_MAX)
            instr++;

        block_sizes[i] = (int)(instr - fall[i]) + 1;
    }
}