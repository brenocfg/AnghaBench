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
struct tracing_map_elt {int dummy; } ;
struct tracing_map {int dummy; } ;

/* Variables and functions */
 struct tracing_map_elt* __tracing_map_insert (struct tracing_map*,void*,int) ; 

struct tracing_map_elt *tracing_map_lookup(struct tracing_map *map, void *key)
{
	return __tracing_map_insert(map, key, true);
}