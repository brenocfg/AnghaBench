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
struct ceph_mds_session {int /*<<< orphan*/  s_ref; } ;
struct ceph_mds_client {int max_sessions; struct ceph_mds_session** sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  dout (char*,struct ceph_mds_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

struct ceph_mds_session *__ceph_lookup_mds_session(struct ceph_mds_client *mdsc,
						   int mds)
{
	struct ceph_mds_session *session;

	if (mds >= mdsc->max_sessions || !mdsc->sessions[mds])
		return NULL;
	session = mdsc->sessions[mds];
	dout("lookup_mds_session %p %d\n", session,
	     refcount_read(&session->s_ref));
	get_session(session);
	return session;
}