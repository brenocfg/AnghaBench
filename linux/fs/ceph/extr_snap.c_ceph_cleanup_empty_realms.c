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
struct ceph_mds_client {int /*<<< orphan*/  snap_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cleanup_empty_realms (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ceph_cleanup_empty_realms(struct ceph_mds_client *mdsc)
{
	down_write(&mdsc->snap_rwsem);
	__cleanup_empty_realms(mdsc);
	up_write(&mdsc->snap_rwsem);
}