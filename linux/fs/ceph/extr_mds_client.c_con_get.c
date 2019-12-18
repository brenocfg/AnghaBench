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
 int /*<<< orphan*/  dout (char*,struct ceph_mds_session*,...) ; 
 scalar_t__ get_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ceph_connection *con_get(struct ceph_connection *con)
{
	struct ceph_mds_session *s = con->private;

	if (get_session(s)) {
		dout("mdsc con_get %p ok (%d)\n", s, refcount_read(&s->s_ref));
		return con;
	}
	dout("mdsc con_get %p FAIL\n", s);
	return NULL;
}