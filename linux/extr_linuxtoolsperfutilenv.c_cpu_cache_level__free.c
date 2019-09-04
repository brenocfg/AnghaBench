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
struct cpu_cache_level {int /*<<< orphan*/  size; int /*<<< orphan*/  map; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void cpu_cache_level__free(struct cpu_cache_level *cache)
{
	free(cache->type);
	free(cache->map);
	free(cache->size);
}