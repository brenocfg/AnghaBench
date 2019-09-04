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

size_t ta_calc_prealloc_elems(size_t nextidx)
{
    if (nextidx >= ((size_t)-1) / 2 - 1)
        return (size_t)-1;
    return (nextidx + 1) * 2;
}