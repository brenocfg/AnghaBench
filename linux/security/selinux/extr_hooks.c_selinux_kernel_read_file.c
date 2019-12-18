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
struct file {int dummy; } ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;

/* Variables and functions */
#define  READING_MODULE 128 
 int selinux_kernel_module_from_file (struct file*) ; 

__attribute__((used)) static int selinux_kernel_read_file(struct file *file,
				    enum kernel_read_file_id id)
{
	int rc = 0;

	switch (id) {
	case READING_MODULE:
		rc = selinux_kernel_module_from_file(file);
		break;
	default:
		break;
	}

	return rc;
}