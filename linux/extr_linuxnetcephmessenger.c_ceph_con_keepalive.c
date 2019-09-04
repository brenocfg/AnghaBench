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
struct ceph_connection {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_FLAG_KEEPALIVE_PENDING ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 int /*<<< orphan*/  clear_standby (struct ceph_connection*) ; 
 int /*<<< orphan*/  con_flag_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ con_flag_test_and_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_con (struct ceph_connection*) ; 

void ceph_con_keepalive(struct ceph_connection *con)
{
	dout("con_keepalive %p\n", con);
	mutex_lock(&con->mutex);
	clear_standby(con);
	con_flag_set(con, CON_FLAG_KEEPALIVE_PENDING);
	mutex_unlock(&con->mutex);

	if (con_flag_test_and_set(con, CON_FLAG_WRITE_PENDING) == 0)
		queue_con(con);
}