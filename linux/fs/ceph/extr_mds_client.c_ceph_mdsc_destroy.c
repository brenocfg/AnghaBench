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
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_mdsc_stop (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_msgr_flush () ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_client*) ; 
 int /*<<< orphan*/  kfree (struct ceph_mds_client*) ; 

void ceph_mdsc_destroy(struct ceph_fs_client *fsc)
{
	struct ceph_mds_client *mdsc = fsc->mdsc;
	dout("mdsc_destroy %p\n", mdsc);

	if (!mdsc)
		return;

	/* flush out any connection work with references to us */
	ceph_msgr_flush();

	ceph_mdsc_stop(mdsc);

	fsc->mdsc = NULL;
	kfree(mdsc);
	dout("mdsc_destroy %p done\n", mdsc);
}