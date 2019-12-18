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
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*,int) ; 
 int ima_read_file (struct file*,int) ; 
 int /*<<< orphan*/  kernel_read_file ; 

int security_kernel_read_file(struct file *file, enum kernel_read_file_id id)
{
	int ret;

	ret = call_int_hook(kernel_read_file, 0, file, id);
	if (ret)
		return ret;
	return ima_read_file(file, id);
}