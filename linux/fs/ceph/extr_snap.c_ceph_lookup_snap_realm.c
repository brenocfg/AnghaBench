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
struct ceph_snap_realm {int dummy; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 struct ceph_snap_realm* __lookup_snap_realm (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_get_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 

struct ceph_snap_realm *ceph_lookup_snap_realm(struct ceph_mds_client *mdsc,
					       u64 ino)
{
	struct ceph_snap_realm *r;
	r = __lookup_snap_realm(mdsc, ino);
	if (r)
		ceph_get_snap_realm(mdsc, r);
	return r;
}