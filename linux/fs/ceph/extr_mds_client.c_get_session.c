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

/* Variables and functions */
 int /*<<< orphan*/  dout (char*,struct ceph_mds_session*,...) ; 
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ceph_mds_session *get_session(struct ceph_mds_session *s)
{
	if (refcount_inc_not_zero(&s->s_ref)) {
		dout("mdsc get_session %p %d -> %d\n", s,
		     refcount_read(&s->s_ref)-1, refcount_read(&s->s_ref));
		return s;
	} else {
		dout("mdsc get_session %p 0 -- FAIL\n", s);
		return NULL;
	}
}