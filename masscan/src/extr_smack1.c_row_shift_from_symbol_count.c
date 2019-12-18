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

/* Variables and functions */

__attribute__((used)) static unsigned
row_shift_from_symbol_count(unsigned symbol_count)
{
    unsigned row_shift = 1;

    symbol_count++;

    while ((unsigned)(1 << row_shift) < symbol_count)
        row_shift++;

    return row_shift;
}