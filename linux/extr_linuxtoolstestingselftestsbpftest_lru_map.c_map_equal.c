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
 scalar_t__ map_subset (int,int) ; 

__attribute__((used)) static int map_equal(int lru_map, int expected)
{
	return map_subset(lru_map, expected) && map_subset(expected, lru_map);
}