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
struct TYPE_2__ {unsigned int size; unsigned int watermark; } ;
struct rte_ring {TYPE_1__ prod; } ;

/* Variables and functions */
 int EINVAL ; 

int
rte_ring_set_water_mark(struct rte_ring *r, unsigned count)
{
    if (count >= r->prod.size)
        return -EINVAL;

    /* if count is 0, disable the watermarking */
    if (count == 0)
        count = r->prod.size;

    r->prod.watermark = count;
    return 0;
}