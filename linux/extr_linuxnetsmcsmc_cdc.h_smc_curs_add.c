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
union smc_host_cursor {int count; int /*<<< orphan*/  wrap; } ;

/* Variables and functions */

__attribute__((used)) static inline void smc_curs_add(int size, union smc_host_cursor *curs,
				int value)
{
	curs->count += value;
	if (curs->count >= size) {
		curs->wrap++;
		curs->count -= size;
	}
}