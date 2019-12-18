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
 int /*<<< orphan*/  current_clos ; 
 int isst_clos_associate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_display_result (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void set_clos_assoc_for_cpu(int cpu, void *arg1, void *arg2, void *arg3,
				   void *arg4)
{
	int ret;

	ret = isst_clos_associate(cpu, current_clos);
	if (ret)
		perror("isst_clos_associate");
	else
		isst_display_result(cpu, outf, "core-power", "assoc", ret);
}