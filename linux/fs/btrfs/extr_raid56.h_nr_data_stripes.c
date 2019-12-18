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
struct map_lookup {int num_stripes; } ;

/* Variables and functions */
 int nr_parity_stripes (struct map_lookup const*) ; 

__attribute__((used)) static inline int nr_data_stripes(const struct map_lookup *map)
{
	return map->num_stripes - nr_parity_stripes(map);
}