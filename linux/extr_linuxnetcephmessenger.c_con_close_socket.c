#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ceph_connection {TYPE_2__* sock; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* shutdown ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CON_FLAG_SOCK_CLOSED ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  con_flag_clear (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_sock_state_closed (struct ceph_connection*) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*,TYPE_2__*) ; 
 int /*<<< orphan*/  sock_release (TYPE_2__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int con_close_socket(struct ceph_connection *con)
{
	int rc = 0;

	dout("con_close_socket on %p sock %p\n", con, con->sock);
	if (con->sock) {
		rc = con->sock->ops->shutdown(con->sock, SHUT_RDWR);
		sock_release(con->sock);
		con->sock = NULL;
	}

	/*
	 * Forcibly clear the SOCK_CLOSED flag.  It gets set
	 * independent of the connection mutex, and we could have
	 * received a socket close event before we had the chance to
	 * shut the socket down.
	 */
	con_flag_clear(con, CON_FLAG_SOCK_CLOSED);

	con_sock_state_closed(con);
	return rc;
}