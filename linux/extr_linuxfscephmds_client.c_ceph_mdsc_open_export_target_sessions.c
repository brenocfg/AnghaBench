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
 int /*<<< orphan*/  __open_export_target_sessions (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ceph_mdsc_open_export_target_sessions(struct ceph_mds_client *mdsc,
					   struct ceph_mds_session *session)
{
	mutex_lock(&mdsc->mutex);
	__open_export_target_sessions(mdsc, session);
	mutex_unlock(&mdsc->mutex);
}