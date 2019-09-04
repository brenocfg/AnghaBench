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
struct ceph_connection {struct ceph_mds_session* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_session*,scalar_t__) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void con_put(struct ceph_connection *con)
{
	struct ceph_mds_session *s = con->private;

	dout("mdsc con_put %p (%d)\n", s, refcount_read(&s->s_ref) - 1);
	ceph_put_mds_session(s);
}