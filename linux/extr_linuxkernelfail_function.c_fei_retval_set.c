#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct fei_attr {scalar_t__ retval; TYPE_1__ kp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned long adjust_error_retval (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  fei_attr_is_valid (struct fei_attr*) ; 
 int /*<<< orphan*/  fei_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fei_retval_set(void *data, u64 val)
{
	struct fei_attr *attr = data;
	unsigned long retv = (unsigned long)val;
	int err = 0;

	mutex_lock(&fei_lock);
	/*
	 * Since this operation can be done after retval file is removed,
	 * It is safer to check the attr is still valid before accessing
	 * its member.
	 */
	if (!fei_attr_is_valid(attr)) {
		err = -ENOENT;
		goto out;
	}

	if (attr->kp.addr) {
		if (adjust_error_retval((unsigned long)attr->kp.addr,
					val) != retv)
			err = -EINVAL;
	}
	if (!err)
		attr->retval = val;
out:
	mutex_unlock(&fei_lock);

	return err;
}