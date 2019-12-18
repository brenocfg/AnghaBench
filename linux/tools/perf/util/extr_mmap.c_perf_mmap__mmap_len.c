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
struct TYPE_2__ {size_t mask; } ;
struct mmap {TYPE_1__ core; } ;

/* Variables and functions */
 size_t page_size ; 

size_t perf_mmap__mmap_len(struct mmap *map)
{
	return map->core.mask + 1 + page_size;
}