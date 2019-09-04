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
struct ceph_mds_session {int /*<<< orphan*/  s_mds; struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_connection {struct ceph_mds_session* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_mds_reconnect (struct ceph_mds_client*,struct ceph_mds_session*) ; 

__attribute__((used)) static void peer_reset(struct ceph_connection *con)
{
	struct ceph_mds_session *s = con->private;
	struct ceph_mds_client *mdsc = s->s_mdsc;

	pr_warn("mds%d closed our session\n", s->s_mds);
	send_mds_reconnect(mdsc, s);
}