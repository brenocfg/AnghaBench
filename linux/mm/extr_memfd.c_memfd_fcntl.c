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
 long EINVAL ; 
#define  F_ADD_SEALS 129 
#define  F_GET_SEALS 128 
 unsigned long UINT_MAX ; 
 long memfd_add_seals (struct file*,unsigned long) ; 
 long memfd_get_seals (struct file*) ; 

long memfd_fcntl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long error;

	switch (cmd) {
	case F_ADD_SEALS:
		/* disallow upper 32bit */
		if (arg > UINT_MAX)
			return -EINVAL;

		error = memfd_add_seals(file, arg);
		break;
	case F_GET_SEALS:
		error = memfd_get_seals(file);
		break;
	default:
		error = -EINVAL;
		break;
	}

	return error;
}