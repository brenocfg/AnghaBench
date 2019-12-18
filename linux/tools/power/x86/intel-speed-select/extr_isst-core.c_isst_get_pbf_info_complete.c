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
struct isst_pbf_info {int /*<<< orphan*/  core_cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpu_set (int /*<<< orphan*/ ) ; 

void isst_get_pbf_info_complete(struct isst_pbf_info *pbf_info)
{
	free_cpu_set(pbf_info->core_cpumask);
}