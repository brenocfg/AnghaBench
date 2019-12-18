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
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct ceph_mds_session* __open_export_target_session (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  dout (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct ceph_mds_session *
ceph_mdsc_open_export_target_session(struct ceph_mds_client *mdsc, int target)
{
	struct ceph_mds_session *session;

	dout("open_export_target_session to mds%d\n", target);

	mutex_lock(&mdsc->mutex);
	session = __open_export_target_session(mdsc, target);
	mutex_unlock(&mdsc->mutex);

	return session;
}