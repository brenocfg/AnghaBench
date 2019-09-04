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
struct ceph_timespec {int dummy; } ;
struct ceph_connection {int /*<<< orphan*/  last_keepalive_ack; } ;
typedef  int /*<<< orphan*/  ceph_ts ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_decode_timespec64 (int /*<<< orphan*/ *,struct ceph_timespec*) ; 
 int /*<<< orphan*/  prepare_read_tag (struct ceph_connection*) ; 
 int read_partial (struct ceph_connection*,size_t,size_t,struct ceph_timespec*) ; 

__attribute__((used)) static int read_keepalive_ack(struct ceph_connection *con)
{
	struct ceph_timespec ceph_ts;
	size_t size = sizeof(ceph_ts);
	int ret = read_partial(con, size, size, &ceph_ts);
	if (ret <= 0)
		return ret;
	ceph_decode_timespec64(&con->last_keepalive_ack, &ceph_ts);
	prepare_read_tag(con);
	return 1;
}