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
struct ceph_mds_session {int /*<<< orphan*/  s_cap_release_work; } ;
struct ceph_mds_client {TYPE_1__* fsc; scalar_t__ stopping; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  get_session (struct ceph_mds_session*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_flush_cap_releases(struct ceph_mds_client *mdsc,
		             struct ceph_mds_session *session)
{
	if (mdsc->stopping)
		return;

	get_session(session);
	if (queue_work(mdsc->fsc->cap_wq,
		       &session->s_cap_release_work)) {
		dout("cap release work queued\n");
	} else {
		ceph_put_mds_session(session);
		dout("failed to queue cap release work\n");
	}
}