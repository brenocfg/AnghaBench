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
struct qrtr_sock {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EACCES ; 
 int EADDRINUSE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QRTR_MAX_EPH_SOCKET ; 
 int QRTR_MIN_EPH_SOCKET ; 
 int QRTR_PORT_CTRL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct qrtr_sock*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qrtr_port_lock ; 
 int /*<<< orphan*/  qrtr_ports ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qrtr_port_assign(struct qrtr_sock *ipc, int *port)
{
	int rc;

	mutex_lock(&qrtr_port_lock);
	if (!*port) {
		rc = idr_alloc(&qrtr_ports, ipc,
			       QRTR_MIN_EPH_SOCKET, QRTR_MAX_EPH_SOCKET + 1,
			       GFP_ATOMIC);
		if (rc >= 0)
			*port = rc;
	} else if (*port < QRTR_MIN_EPH_SOCKET && !capable(CAP_NET_ADMIN)) {
		rc = -EACCES;
	} else if (*port == QRTR_PORT_CTRL) {
		rc = idr_alloc(&qrtr_ports, ipc, 0, 1, GFP_ATOMIC);
	} else {
		rc = idr_alloc(&qrtr_ports, ipc, *port, *port + 1, GFP_ATOMIC);
		if (rc >= 0)
			*port = rc;
	}
	mutex_unlock(&qrtr_port_lock);

	if (rc == -ENOSPC)
		return -EADDRINUSE;
	else if (rc < 0)
		return rc;

	sock_hold(&ipc->sk);

	return 0;
}