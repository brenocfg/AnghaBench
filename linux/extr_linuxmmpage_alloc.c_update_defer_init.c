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
typedef  int /*<<< orphan*/  pg_data_t ;

/* Variables and functions */

__attribute__((used)) static inline bool update_defer_init(pg_data_t *pgdat,
				unsigned long pfn, unsigned long zone_end,
				unsigned long *nr_initialised)
{
	return true;
}