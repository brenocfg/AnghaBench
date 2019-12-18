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
struct ceph_mds_session {scalar_t__ s_state; int /*<<< orphan*/  s_mutex; int /*<<< orphan*/  s_waiting; } ;
struct ceph_mds_client {int max_sessions; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waiting_for_map; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_SESSION_CLOSING ; 
 scalar_t__ CEPH_MDS_SESSION_REJECTED ; 
 struct ceph_mds_session* __ceph_lookup_mds_session (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  __close_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  __unregister_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  __wake_requests (struct ceph_mds_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  cleanup_session_requests (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  kick_requests (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_session_caps (struct ceph_mds_session*) ; 

void ceph_mdsc_force_umount(struct ceph_mds_client *mdsc)
{
	struct ceph_mds_session *session;
	int mds;

	dout("force umount\n");

	mutex_lock(&mdsc->mutex);
	for (mds = 0; mds < mdsc->max_sessions; mds++) {
		session = __ceph_lookup_mds_session(mdsc, mds);
		if (!session)
			continue;

		if (session->s_state == CEPH_MDS_SESSION_REJECTED)
			__unregister_session(mdsc, session);
		__wake_requests(mdsc, &session->s_waiting);
		mutex_unlock(&mdsc->mutex);

		mutex_lock(&session->s_mutex);
		__close_session(mdsc, session);
		if (session->s_state == CEPH_MDS_SESSION_CLOSING) {
			cleanup_session_requests(mdsc, session);
			remove_session_caps(session);
		}
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);

		mutex_lock(&mdsc->mutex);
		kick_requests(mdsc, mds);
	}
	__wake_requests(mdsc, &mdsc->waiting_for_map);
	mutex_unlock(&mdsc->mutex);
}