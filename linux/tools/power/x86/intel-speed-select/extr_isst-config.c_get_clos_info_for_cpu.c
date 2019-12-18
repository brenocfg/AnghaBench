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
 int /*<<< orphan*/  isst_clos_display_clos_information (int,int /*<<< orphan*/ ,int,int) ; 
 int isst_clos_get_clos_information (int,int*,int*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void get_clos_info_for_cpu(int cpu, void *arg1, void *arg2, void *arg3,
				  void *arg4)
{
	int enable, ret, prio_type;

	ret = isst_clos_get_clos_information(cpu, &enable, &prio_type);
	if (ret)
		perror("isst_clos_get_info");
	else
		isst_clos_display_clos_information(cpu, outf, enable, prio_type);
}