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
struct isst_pkg_ctdp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fact_trl ; 
 int /*<<< orphan*/  isst_display_result (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int isst_get_ctdp_levels (int,struct isst_pkg_ctdp*) ; 
 int isst_set_pbf_fact_status (int,int /*<<< orphan*/ ,int) ; 
 int isst_set_trl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_set_trl_from_current_tdp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void set_fact_for_cpu(int cpu, void *arg1, void *arg2, void *arg3,
			     void *arg4)
{
	int ret;
	int status = *(int *)arg4;

	ret = isst_set_pbf_fact_status(cpu, 0, status);
	if (ret)
		perror("isst_set_fact");
	else {
		if (status) {
			struct isst_pkg_ctdp pkg_dev;

			ret = isst_get_ctdp_levels(cpu, &pkg_dev);
			if (ret) {
				isst_display_result(cpu, outf, "turbo-freq",
						    "enable", ret);
				return;
			}
			ret = isst_set_trl(cpu, fact_trl);
			isst_display_result(cpu, outf, "turbo-freq", "enable",
					    ret);
		} else {
			/* Since we modified TRL during Fact enable, restore it */
			isst_set_trl_from_current_tdp(cpu, fact_trl);
			isst_display_result(cpu, outf, "turbo-freq", "disable",
					    ret);
		}
	}
}