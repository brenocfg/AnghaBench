#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ceph_mds_session {int s_mds; } ;
struct ceph_mds_info {int num_export_targets; int /*<<< orphan*/ * export_targets; } ;
struct ceph_mds_client {TYPE_1__* mdsmap; } ;
struct TYPE_2__ {int m_num_mds; struct ceph_mds_info* m_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct ceph_mds_session*) ; 
 struct ceph_mds_session* __open_export_target_session (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*,int,int) ; 

__attribute__((used)) static void __open_export_target_sessions(struct ceph_mds_client *mdsc,
					  struct ceph_mds_session *session)
{
	struct ceph_mds_info *mi;
	struct ceph_mds_session *ts;
	int i, mds = session->s_mds;

	if (mds >= mdsc->mdsmap->m_num_mds)
		return;

	mi = &mdsc->mdsmap->m_info[mds];
	dout("open_export_target_sessions for mds%d (%d targets)\n",
	     session->s_mds, mi->num_export_targets);

	for (i = 0; i < mi->num_export_targets; i++) {
		ts = __open_export_target_session(mdsc, mi->export_targets[i]);
		if (!IS_ERR(ts))
			ceph_put_mds_session(ts);
	}
}