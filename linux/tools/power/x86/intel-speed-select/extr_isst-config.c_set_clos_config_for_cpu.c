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
struct isst_clos_config {int /*<<< orphan*/  clos_desired; int /*<<< orphan*/  clos_max; int /*<<< orphan*/  clos_min; int /*<<< orphan*/  clos_prop_prio; int /*<<< orphan*/  epp; int /*<<< orphan*/  die_id; int /*<<< orphan*/  pkg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  clos_desired ; 
 int /*<<< orphan*/  clos_epp ; 
 int /*<<< orphan*/  clos_max ; 
 int /*<<< orphan*/  clos_min ; 
 int /*<<< orphan*/  clos_prop_prio ; 
 int /*<<< orphan*/  current_clos ; 
 int /*<<< orphan*/  get_physical_die_id (int) ; 
 int /*<<< orphan*/  get_physical_package_id (int) ; 
 int /*<<< orphan*/  isst_display_result (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int isst_set_clos (int,int /*<<< orphan*/ ,struct isst_clos_config*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void set_clos_config_for_cpu(int cpu, void *arg1, void *arg2, void *arg3,
				    void *arg4)
{
	struct isst_clos_config clos_config;
	int ret;

	clos_config.pkg_id = get_physical_package_id(cpu);
	clos_config.die_id = get_physical_die_id(cpu);

	clos_config.epp = clos_epp;
	clos_config.clos_prop_prio = clos_prop_prio;
	clos_config.clos_min = clos_min;
	clos_config.clos_max = clos_max;
	clos_config.clos_desired = clos_desired;
	ret = isst_set_clos(cpu, current_clos, &clos_config);
	if (ret)
		perror("isst_set_clos");
	else
		isst_display_result(cpu, outf, "core-power", "config", ret);
}