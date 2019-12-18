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
struct isst_clos_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_clos ; 
 int /*<<< orphan*/  isst_clos_display_information (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct isst_clos_config*) ; 
 int isst_pm_get_clos (int,int /*<<< orphan*/ ,struct isst_clos_config*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void dump_clos_config_for_cpu(int cpu, void *arg1, void *arg2,
				     void *arg3, void *arg4)
{
	struct isst_clos_config clos_config;
	int ret;

	ret = isst_pm_get_clos(cpu, current_clos, &clos_config);
	if (ret)
		perror("isst_pm_get_clos");
	else
		isst_clos_display_information(cpu, outf, current_clos,
					      &clos_config);
}