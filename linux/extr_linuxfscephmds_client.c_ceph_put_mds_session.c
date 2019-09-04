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
struct TYPE_2__ {scalar_t__ authorizer; } ;
struct ceph_mds_session {TYPE_1__ s_auth; int /*<<< orphan*/  s_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_auth_destroy_authorizer (scalar_t__) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_session*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ceph_mds_session*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

void ceph_put_mds_session(struct ceph_mds_session *s)
{
	dout("mdsc put_session %p %d -> %d\n", s,
	     refcount_read(&s->s_ref), refcount_read(&s->s_ref)-1);
	if (refcount_dec_and_test(&s->s_ref)) {
		if (s->s_auth.authorizer)
			ceph_auth_destroy_authorizer(s->s_auth.authorizer);
		kfree(s);
	}
}