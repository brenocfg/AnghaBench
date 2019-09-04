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
struct ceph_mds_client {scalar_t__ caps_min_count; int /*<<< orphan*/  caps_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_adjust_min_caps(struct ceph_mds_client *mdsc, int delta)
{
	spin_lock(&mdsc->caps_list_lock);
	mdsc->caps_min_count += delta;
	BUG_ON(mdsc->caps_min_count < 0);
	spin_unlock(&mdsc->caps_list_lock);
}