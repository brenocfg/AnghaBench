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
struct isst_fact_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fact_avx ; 
 int /*<<< orphan*/  fact_bucket ; 
 int /*<<< orphan*/  isst_fact_display_information (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct isst_fact_info*) ; 
 int isst_get_fact_info (int,int /*<<< orphan*/ ,struct isst_fact_info*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  tdp_level ; 

__attribute__((used)) static void dump_fact_config_for_cpu(int cpu, void *arg1, void *arg2,
				     void *arg3, void *arg4)
{
	struct isst_fact_info fact_info;
	int ret;

	ret = isst_get_fact_info(cpu, tdp_level, &fact_info);
	if (ret)
		perror("isst_get_fact_bucket_info");
	else
		isst_fact_display_information(cpu, outf, tdp_level, fact_bucket,
					      fact_avx, &fact_info);
}