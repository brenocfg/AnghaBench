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
 int QRTR_PORT_CTRL ; 
 struct qrtr_sock* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qrtr_port_lock ; 
 int /*<<< orphan*/  qrtr_ports ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qrtr_sock *qrtr_port_lookup(int port)
{
	struct qrtr_sock *ipc;

	if (port == QRTR_PORT_CTRL)
		port = 0;

	mutex_lock(&qrtr_port_lock);
	ipc = idr_find(&qrtr_ports, port);
	if (ipc)
		sock_hold(&ipc->sk);
	mutex_unlock(&qrtr_port_lock);

	return ipc;
}