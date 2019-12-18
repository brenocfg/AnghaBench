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
typedef  enum kernel_load_data_id { ____Placeholder_kernel_load_data_id } kernel_load_data_id ;

/* Variables and functions */
#define  LOADING_MODULE 128 
 int selinux_kernel_module_from_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_kernel_load_data(enum kernel_load_data_id id)
{
	int rc = 0;

	switch (id) {
	case LOADING_MODULE:
		rc = selinux_kernel_module_from_file(NULL);
	default:
		break;
	}

	return rc;
}