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
struct iscsi_conn {struct cxgbit_sock* context; } ;
struct cxgbit_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ cxgbit_wait_rxq (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  iscsit_thread_check_cpumask (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 

void cxgbit_get_rx_pdu(struct iscsi_conn *conn)
{
	struct cxgbit_sock *csk = conn->context;

	while (!kthread_should_stop()) {
		iscsit_thread_check_cpumask(conn, current, 0);
		if (cxgbit_wait_rxq(csk))
			return;
	}
}