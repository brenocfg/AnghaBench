#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ceph_options {int /*<<< orphan*/  mount_timeout; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_mutex; } ;
struct ceph_mds_client {int max_sessions; int /*<<< orphan*/  delayed_work; int /*<<< orphan*/  cap_reclaim_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cap_delay_list; scalar_t__* sessions; int /*<<< orphan*/  session_close_wq; TYPE_2__* fsc; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ceph_mds_session* __ceph_lookup_mds_session (struct ceph_mds_client*,int) ; 
 scalar_t__ __close_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  __unregister_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_cleanup_empty_realms (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_cleanup_snapid_map (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done_closing_sessions (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  dout (char*) ; 
 struct ceph_mds_session* get_session (scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_session_caps (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ceph_mdsc_close_sessions(struct ceph_mds_client *mdsc)
{
	struct ceph_options *opts = mdsc->fsc->client->options;
	struct ceph_mds_session *session;
	int i;
	int skipped = 0;

	dout("close_sessions\n");

	/* close sessions */
	mutex_lock(&mdsc->mutex);
	for (i = 0; i < mdsc->max_sessions; i++) {
		session = __ceph_lookup_mds_session(mdsc, i);
		if (!session)
			continue;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&session->s_mutex);
		if (__close_session(mdsc, session) <= 0)
			skipped++;
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
		mutex_lock(&mdsc->mutex);
	}
	mutex_unlock(&mdsc->mutex);

	dout("waiting for sessions to close\n");
	wait_event_timeout(mdsc->session_close_wq,
			   done_closing_sessions(mdsc, skipped),
			   ceph_timeout_jiffies(opts->mount_timeout));

	/* tear down remaining sessions */
	mutex_lock(&mdsc->mutex);
	for (i = 0; i < mdsc->max_sessions; i++) {
		if (mdsc->sessions[i]) {
			session = get_session(mdsc->sessions[i]);
			__unregister_session(mdsc, session);
			mutex_unlock(&mdsc->mutex);
			mutex_lock(&session->s_mutex);
			remove_session_caps(session);
			mutex_unlock(&session->s_mutex);
			ceph_put_mds_session(session);
			mutex_lock(&mdsc->mutex);
		}
	}
	WARN_ON(!list_empty(&mdsc->cap_delay_list));
	mutex_unlock(&mdsc->mutex);

	ceph_cleanup_snapid_map(mdsc);
	ceph_cleanup_empty_realms(mdsc);

	cancel_work_sync(&mdsc->cap_reclaim_work);
	cancel_delayed_work_sync(&mdsc->delayed_work); /* cancel timer */

	dout("stopped\n");
}