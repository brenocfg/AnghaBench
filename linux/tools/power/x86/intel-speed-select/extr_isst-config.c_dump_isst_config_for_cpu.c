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
typedef  int /*<<< orphan*/  pkg_dev ;

/* Variables and functions */
 int /*<<< orphan*/  isst_ctdp_display_information (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct isst_pkg_ctdp*) ; 
 int isst_get_process_ctdp (int,int /*<<< orphan*/ ,struct isst_pkg_ctdp*) ; 
 int /*<<< orphan*/  isst_get_process_ctdp_complete (int,struct isst_pkg_ctdp*) ; 
 int /*<<< orphan*/  memset (struct isst_pkg_ctdp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  tdp_level ; 

__attribute__((used)) static void dump_isst_config_for_cpu(int cpu, void *arg1, void *arg2,
				     void *arg3, void *arg4)
{
	struct isst_pkg_ctdp pkg_dev;
	int ret;

	memset(&pkg_dev, 0, sizeof(pkg_dev));
	ret = isst_get_process_ctdp(cpu, tdp_level, &pkg_dev);
	if (ret) {
		perror("isst_get_process_ctdp");
	} else {
		isst_ctdp_display_information(cpu, outf, tdp_level, &pkg_dev);
		isst_get_process_ctdp_complete(cpu, &pkg_dev);
	}
}