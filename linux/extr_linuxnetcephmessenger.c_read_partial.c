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
struct ceph_connection {int in_base_pos; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int ceph_tcp_recvmsg (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int read_partial(struct ceph_connection *con,
			int end, int size, void *object)
{
	while (con->in_base_pos < end) {
		int left = end - con->in_base_pos;
		int have = size - left;
		int ret = ceph_tcp_recvmsg(con->sock, object + have, left);
		if (ret <= 0)
			return ret;
		con->in_base_pos += ret;
	}
	return 1;
}