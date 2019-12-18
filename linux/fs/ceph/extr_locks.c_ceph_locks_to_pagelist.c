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
struct ceph_pagelist {int dummy; } ;
struct ceph_filelock {int dummy; } ;
typedef  int /*<<< orphan*/  nlocks ;
typedef  struct ceph_filelock __le32 ;

/* Variables and functions */
 int ceph_pagelist_append (struct ceph_pagelist*,struct ceph_filelock*,int) ; 
 struct ceph_filelock cpu_to_le32 (int) ; 

int ceph_locks_to_pagelist(struct ceph_filelock *flocks,
			   struct ceph_pagelist *pagelist,
			   int num_fcntl_locks, int num_flock_locks)
{
	int err = 0;
	__le32 nlocks;

	nlocks = cpu_to_le32(num_fcntl_locks);
	err = ceph_pagelist_append(pagelist, &nlocks, sizeof(nlocks));
	if (err)
		goto out_fail;

	if (num_fcntl_locks > 0) {
		err = ceph_pagelist_append(pagelist, flocks,
					   num_fcntl_locks * sizeof(*flocks));
		if (err)
			goto out_fail;
	}

	nlocks = cpu_to_le32(num_flock_locks);
	err = ceph_pagelist_append(pagelist, &nlocks, sizeof(nlocks));
	if (err)
		goto out_fail;

	if (num_flock_locks > 0) {
		err = ceph_pagelist_append(pagelist, &flocks[num_fcntl_locks],
					   num_flock_locks * sizeof(*flocks));
	}
out_fail:
	return err;
}