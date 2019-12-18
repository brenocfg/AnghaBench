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
struct ceph_mds_session {int /*<<< orphan*/  s_mutex; } ;
struct ceph_mds_client {int max_sessions; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct ceph_mds_session* __ceph_lookup_mds_session (struct ceph_mds_client*,int) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lock_unlock_sessions(struct ceph_mds_client *mdsc)
{
	int i;

	mutex_lock(&mdsc->mutex);
	for (i = 0; i < mdsc->max_sessions; i++) {
		struct ceph_mds_session *s = __ceph_lookup_mds_session(mdsc, i);
		if (!s)
			continue;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&s->s_mutex);
		mutex_unlock(&s->s_mutex);
		ceph_put_mds_session(s);
		mutex_lock(&mdsc->mutex);
	}
	mutex_unlock(&mdsc->mutex);
}