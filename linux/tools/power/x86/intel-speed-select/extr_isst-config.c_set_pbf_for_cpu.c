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
 int /*<<< orphan*/  isst_display_result (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int isst_set_pbf_fact_status (int,int,int) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void set_pbf_for_cpu(int cpu, void *arg1, void *arg2, void *arg3,
			    void *arg4)
{
	int ret;
	int status = *(int *)arg4;

	ret = isst_set_pbf_fact_status(cpu, 1, status);
	if (ret) {
		perror("isst_set_pbf");
	} else {
		if (status)
			isst_display_result(cpu, outf, "base-freq", "enable",
					    ret);
		else
			isst_display_result(cpu, outf, "base-freq", "disable",
					    ret);
	}
}