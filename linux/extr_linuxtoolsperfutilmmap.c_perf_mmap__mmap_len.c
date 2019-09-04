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
struct perf_mmap {size_t mask; } ;

/* Variables and functions */
 size_t page_size ; 

size_t perf_mmap__mmap_len(struct perf_mmap *map)
{
	return map->mask + 1 + page_size;
}