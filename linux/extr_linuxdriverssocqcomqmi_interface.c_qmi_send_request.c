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
struct sockaddr_qrtr {int dummy; } ;
struct qmi_txn {int dummy; } ;
struct qmi_handle {int dummy; } ;
struct qmi_elem_info {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QMI_REQUEST ; 
 int /*<<< orphan*/  qmi_send_message (struct qmi_handle*,struct sockaddr_qrtr*,struct qmi_txn*,int /*<<< orphan*/ ,int,size_t,struct qmi_elem_info*,void const*) ; 

ssize_t qmi_send_request(struct qmi_handle *qmi, struct sockaddr_qrtr *sq,
			 struct qmi_txn *txn, int msg_id, size_t len,
			 struct qmi_elem_info *ei, const void *c_struct)
{
	return qmi_send_message(qmi, sq, txn, QMI_REQUEST, msg_id, len, ei,
				c_struct);
}