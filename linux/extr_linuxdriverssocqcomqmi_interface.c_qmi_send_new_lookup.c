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
struct sockaddr_qrtr {int /*<<< orphan*/  sq_port; int /*<<< orphan*/  sq_node; int /*<<< orphan*/  sq_family; } ;
struct TYPE_3__ {void* instance; void* service; } ;
struct qrtr_ctrl_pkt {TYPE_1__ server; void* cmd; } ;
struct qmi_service {int service; int version; int instance; } ;
struct TYPE_4__ {int /*<<< orphan*/  sq_node; int /*<<< orphan*/  sq_family; } ;
struct qmi_handle {int /*<<< orphan*/  sock_lock; scalar_t__ sock; TYPE_2__ sq; } ;
struct msghdr {int msg_namelen; struct sockaddr_qrtr* msg_name; } ;
struct kvec {int member_1; struct qrtr_ctrl_pkt* member_0; } ;
typedef  int /*<<< orphan*/  sq ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  QRTR_PORT_CTRL ; 
 int QRTR_TYPE_NEW_LOOKUP ; 
 void* cpu_to_le32 (int) ; 
 int kernel_sendmsg (scalar_t__,struct msghdr*,struct kvec*,int,int) ; 
 int /*<<< orphan*/  memset (struct qrtr_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void qmi_send_new_lookup(struct qmi_handle *qmi, struct qmi_service *svc)
{
	struct qrtr_ctrl_pkt pkt;
	struct sockaddr_qrtr sq;
	struct msghdr msg = { };
	struct kvec iv = { &pkt, sizeof(pkt) };
	int ret;

	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_NEW_LOOKUP);
	pkt.server.service = cpu_to_le32(svc->service);
	pkt.server.instance = cpu_to_le32(svc->version | svc->instance << 8);

	sq.sq_family = qmi->sq.sq_family;
	sq.sq_node = qmi->sq.sq_node;
	sq.sq_port = QRTR_PORT_CTRL;

	msg.msg_name = &sq;
	msg.msg_namelen = sizeof(sq);

	mutex_lock(&qmi->sock_lock);
	if (qmi->sock) {
		ret = kernel_sendmsg(qmi->sock, &msg, &iv, 1, sizeof(pkt));
		if (ret < 0)
			pr_err("failed to send lookup registration: %d\n", ret);
	}
	mutex_unlock(&qmi->sock_lock);
}