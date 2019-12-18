#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ prev; } ;
struct mmap {TYPE_2__ auxtrace_mmap; TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ perf_mmap__read_head (struct mmap*) ; 

__attribute__((used)) static bool perf_mmap__empty(struct mmap *map)
{
	return perf_mmap__read_head(map) == map->core.prev && !map->auxtrace_mmap.base;
}