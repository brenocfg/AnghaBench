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
struct ceph_connection {scalar_t__ state; int /*<<< orphan*/  connect_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_FLAG_KEEPALIVE_PENDING ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 scalar_t__ CON_STATE_PREOPEN ; 
 scalar_t__ CON_STATE_STANDBY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_flag_test (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 

__attribute__((used)) static void clear_standby(struct ceph_connection *con)
{
	/* come back from STANDBY? */
	if (con->state == CON_STATE_STANDBY) {
		dout("clear_standby %p and ++connect_seq\n", con);
		con->state = CON_STATE_PREOPEN;
		con->connect_seq++;
		WARN_ON(con_flag_test(con, CON_FLAG_WRITE_PENDING));
		WARN_ON(con_flag_test(con, CON_FLAG_KEEPALIVE_PENDING));
	}
}