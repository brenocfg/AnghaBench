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

/* Variables and functions */
 int EINVAL ; 
 unsigned int* memfd_file_seals_ptr (struct file*) ; 

__attribute__((used)) static int memfd_get_seals(struct file *file)
{
	unsigned int *seals = memfd_file_seals_ptr(file);

	return seals ? *seals : -EINVAL;
}