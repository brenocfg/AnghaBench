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
struct padata_instance {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int PADATA_INVALID ; 
 int /*<<< orphan*/  __padata_start (struct padata_instance*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int padata_start(struct padata_instance *pinst)
{
	int err = 0;

	mutex_lock(&pinst->lock);

	if (pinst->flags & PADATA_INVALID)
		err = -EINVAL;

	__padata_start(pinst);

	mutex_unlock(&pinst->lock);

	return err;
}