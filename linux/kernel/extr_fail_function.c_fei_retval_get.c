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
typedef  int /*<<< orphan*/  u64 ;
struct fei_attr {int /*<<< orphan*/  retval; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  fei_attr_is_valid (struct fei_attr*) ; 
 int /*<<< orphan*/  fei_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fei_retval_get(void *data, u64 *val)
{
	struct fei_attr *attr = data;
	int err = 0;

	mutex_lock(&fei_lock);
	/* Here we also validate @attr to ensure it still exists. */
	if (!fei_attr_is_valid(attr))
		err = -ENOENT;
	else
		*val = attr->retval;
	mutex_unlock(&fei_lock);

	return err;
}