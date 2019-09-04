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
struct tracing_map {int dummy; } ;

/* Variables and functions */
 int tracing_map_add_field (struct tracing_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_map_cmp_atomic64 ; 

int tracing_map_add_sum_field(struct tracing_map *map)
{
	return tracing_map_add_field(map, tracing_map_cmp_atomic64);
}