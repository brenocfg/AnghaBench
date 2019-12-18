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
struct ceph_mds_session {size_t s_mds; int /*<<< orphan*/  s_con; scalar_t__ s_state; } ;
struct ceph_mds_client {int /*<<< orphan*/  num_sessions; struct ceph_mds_session** sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_con_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*,size_t,struct ceph_mds_session*) ; 

__attribute__((used)) static void __unregister_session(struct ceph_mds_client *mdsc,
			       struct ceph_mds_session *s)
{
	dout("__unregister_session mds%d %p\n", s->s_mds, s);
	BUG_ON(mdsc->sessions[s->s_mds] != s);
	mdsc->sessions[s->s_mds] = NULL;
	s->s_state = 0;
	ceph_con_close(&s->s_con);
	ceph_put_mds_session(s);
	atomic_dec(&mdsc->num_sessions);
}