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
struct ceph_mds_client {int /*<<< orphan*/  mutex; TYPE_1__* mdsmap; } ;
struct ceph_ioctl_layout {int object_size; int stripe_unit; scalar_t__ data_pool; } ;
struct TYPE_2__ {int m_num_data_pg_pools; scalar_t__* m_data_pg_pools; } ;

/* Variables and functions */
 long EINVAL ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long __validate_layout(struct ceph_mds_client *mdsc,
			      struct ceph_ioctl_layout *l)
{
	int i, err;

	/* validate striping parameters */
	if ((l->object_size & ~PAGE_MASK) ||
	    (l->stripe_unit & ~PAGE_MASK) ||
	    ((unsigned)l->stripe_unit != 0 &&
	     ((unsigned)l->object_size % (unsigned)l->stripe_unit)))
		return -EINVAL;

	/* make sure it's a valid data pool */
	mutex_lock(&mdsc->mutex);
	err = -EINVAL;
	for (i = 0; i < mdsc->mdsmap->m_num_data_pg_pools; i++)
		if (mdsc->mdsmap->m_data_pg_pools[i] == l->data_pool) {
			err = 0;
			break;
		}
	mutex_unlock(&mdsc->mutex);
	if (err)
		return err;

	return 0;
}