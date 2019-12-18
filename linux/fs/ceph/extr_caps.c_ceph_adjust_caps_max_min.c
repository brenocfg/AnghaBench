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
struct ceph_mount_options {int max_readdir; int caps_max; } ;
struct ceph_mds_client {int caps_min_count; int caps_use_max; int /*<<< orphan*/  caps_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_adjust_caps_max_min(struct ceph_mds_client *mdsc,
			      struct ceph_mount_options *fsopt)
{
	spin_lock(&mdsc->caps_list_lock);
	mdsc->caps_min_count = fsopt->max_readdir;
	if (mdsc->caps_min_count < 1024)
		mdsc->caps_min_count = 1024;
	mdsc->caps_use_max = fsopt->caps_max;
	if (mdsc->caps_use_max > 0 &&
	    mdsc->caps_use_max < mdsc->caps_min_count)
		mdsc->caps_use_max = mdsc->caps_min_count;
	spin_unlock(&mdsc->caps_list_lock);
}