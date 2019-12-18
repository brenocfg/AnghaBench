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
struct ceph_mds_session {int /*<<< orphan*/  s_cap_lock; scalar_t__ s_cap_ttl; int /*<<< orphan*/  s_mds; scalar_t__ s_renew_requested; } ;
struct ceph_mds_client {TYPE_1__* mdsmap; } ;
struct TYPE_2__ {int m_session_timeout; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RENEWCAPS ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_session_caps (struct ceph_mds_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renewed_caps(struct ceph_mds_client *mdsc,
			 struct ceph_mds_session *session, int is_renew)
{
	int was_stale;
	int wake = 0;

	spin_lock(&session->s_cap_lock);
	was_stale = is_renew && time_after_eq(jiffies, session->s_cap_ttl);

	session->s_cap_ttl = session->s_renew_requested +
		mdsc->mdsmap->m_session_timeout*HZ;

	if (was_stale) {
		if (time_before(jiffies, session->s_cap_ttl)) {
			pr_info("mds%d caps renewed\n", session->s_mds);
			wake = 1;
		} else {
			pr_info("mds%d caps still stale\n", session->s_mds);
		}
	}
	dout("renewed_caps mds%d ttl now %lu, was %s, now %s\n",
	     session->s_mds, session->s_cap_ttl, was_stale ? "stale" : "fresh",
	     time_before(jiffies, session->s_cap_ttl) ? "stale" : "fresh");
	spin_unlock(&session->s_cap_lock);

	if (wake)
		wake_up_session_caps(session, RENEWCAPS);
}