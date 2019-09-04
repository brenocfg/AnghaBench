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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct perf_mmap {scalar_t__ prev; TYPE_1__ auxtrace_mmap; } ;

/* Variables and functions */
 scalar_t__ perf_mmap__read_head (struct perf_mmap*) ; 

__attribute__((used)) static bool perf_mmap__empty(struct perf_mmap *map)
{
	return perf_mmap__read_head(map) == map->prev && !map->auxtrace_mmap.base;
}