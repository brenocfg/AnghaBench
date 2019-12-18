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
struct ceph_mds_session {int s_nr_caps; int /*<<< orphan*/  s_mds; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_flush_cap_releases (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_iterate_session_caps (struct ceph_mds_session*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  trim_caps_cb ; 

int ceph_trim_caps(struct ceph_mds_client *mdsc,
		   struct ceph_mds_session *session,
		   int max_caps)
{
	int trim_caps = session->s_nr_caps - max_caps;

	dout("trim_caps mds%d start: %d / %d, trim %d\n",
	     session->s_mds, session->s_nr_caps, max_caps, trim_caps);
	if (trim_caps > 0) {
		int remaining = trim_caps;

		ceph_iterate_session_caps(session, trim_caps_cb, &remaining);
		dout("trim_caps mds%d done: %d / %d, trimmed %d\n",
		     session->s_mds, session->s_nr_caps, max_caps,
			trim_caps - remaining);
	}

	ceph_flush_cap_releases(mdsc, session);
	return 0;
}