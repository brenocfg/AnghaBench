#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_qrtr {int sq_port; int /*<<< orphan*/  sq_node; int /*<<< orphan*/  sq_family; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int sq_port; int sq_node; } ;
struct qrtr_sock {int /*<<< orphan*/  sk; TYPE_2__ us; } ;
struct TYPE_3__ {void* port; void* node; } ;
struct qrtr_ctrl_pkt {TYPE_1__ client; void* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_QIPCRTR ; 
 int /*<<< orphan*/  QRTR_NODE_BCAST ; 
 int QRTR_PORT_CTRL ; 
 int QRTR_TYPE_DEL_CLIENT ; 
 int /*<<< orphan*/  __sock_put (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* qrtr_alloc_ctrl_packet (struct qrtr_ctrl_pkt**) ; 
 int /*<<< orphan*/  qrtr_bcast_enqueue (int /*<<< orphan*/ *,struct sk_buff*,int,TYPE_2__*,struct sockaddr_qrtr*) ; 
 int /*<<< orphan*/  qrtr_port_lock ; 
 int /*<<< orphan*/  qrtr_ports ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qrtr_port_remove(struct qrtr_sock *ipc)
{
	struct qrtr_ctrl_pkt *pkt;
	struct sk_buff *skb;
	int port = ipc->us.sq_port;
	struct sockaddr_qrtr to;

	to.sq_family = AF_QIPCRTR;
	to.sq_node = QRTR_NODE_BCAST;
	to.sq_port = QRTR_PORT_CTRL;

	skb = qrtr_alloc_ctrl_packet(&pkt);
	if (skb) {
		pkt->cmd = cpu_to_le32(QRTR_TYPE_DEL_CLIENT);
		pkt->client.node = cpu_to_le32(ipc->us.sq_node);
		pkt->client.port = cpu_to_le32(ipc->us.sq_port);

		skb_set_owner_w(skb, &ipc->sk);
		qrtr_bcast_enqueue(NULL, skb, QRTR_TYPE_DEL_CLIENT, &ipc->us,
				   &to);
	}

	if (port == QRTR_PORT_CTRL)
		port = 0;

	__sock_put(&ipc->sk);

	mutex_lock(&qrtr_port_lock);
	idr_remove(&qrtr_ports, port);
	mutex_unlock(&qrtr_port_lock);
}