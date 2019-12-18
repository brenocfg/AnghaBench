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
struct ceph_mds_client {struct ceph_fs_client* fsc; } ;
struct ceph_fs_client {int /*<<< orphan*/  sb; scalar_t__ last_auto_reconnect; int /*<<< orphan*/  blacklisted; int /*<<< orphan*/  mount_state; } ;

/* Variables and functions */
 scalar_t__ CEPH_MOUNT_MOUNTED ; 
 int /*<<< orphan*/  CLEANRECOVER ; 
 int HZ ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_force_reconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_test_mount_opt (struct ceph_fs_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void maybe_recover_session(struct ceph_mds_client *mdsc)
{
	struct ceph_fs_client *fsc = mdsc->fsc;

	if (!ceph_test_mount_opt(fsc, CLEANRECOVER))
		return;

	if (READ_ONCE(fsc->mount_state) != CEPH_MOUNT_MOUNTED)
		return;

	if (!READ_ONCE(fsc->blacklisted))
		return;

	if (fsc->last_auto_reconnect &&
	    time_before(jiffies, fsc->last_auto_reconnect + HZ * 60 * 30))
		return;

	pr_info("auto reconnect after blacklisted\n");
	fsc->last_auto_reconnect = jiffies;
	ceph_force_reconnect(fsc->sb);
}