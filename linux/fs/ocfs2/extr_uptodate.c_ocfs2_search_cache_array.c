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
struct TYPE_2__ {scalar_t__* ci_array; } ;
struct ocfs2_caching_info {int ci_num_cached; TYPE_1__ ci_cache; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static int ocfs2_search_cache_array(struct ocfs2_caching_info *ci,
				    sector_t item)
{
	int i;

	for (i = 0; i < ci->ci_num_cached; i++) {
		if (item == ci->ci_cache.ci_array[i])
			return i;
	}

	return -1;
}