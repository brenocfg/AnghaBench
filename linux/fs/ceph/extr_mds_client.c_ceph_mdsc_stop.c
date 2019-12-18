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
struct ceph_mds_client {int /*<<< orphan*/  sessions; scalar_t__ mdsmap; int /*<<< orphan*/  delayed_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_caps_finalize (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_mdsmap_destroy (scalar_t__) ; 
 int /*<<< orphan*/  ceph_pool_perm_destroy (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ceph_mdsc_stop(struct ceph_mds_client *mdsc)
{
	dout("stop\n");
	cancel_delayed_work_sync(&mdsc->delayed_work); /* cancel timer */
	if (mdsc->mdsmap)
		ceph_mdsmap_destroy(mdsc->mdsmap);
	kfree(mdsc->sessions);
	ceph_caps_finalize(mdsc);
	ceph_pool_perm_destroy(mdsc);
}