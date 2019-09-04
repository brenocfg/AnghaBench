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
struct qmi_ops {int /*<<< orphan*/  (* del_client ) (struct qmi_handle*,unsigned int,unsigned int) ;} ;
struct qmi_handle {struct qmi_ops ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct qmi_handle*,unsigned int,unsigned int) ; 

__attribute__((used)) static void qmi_recv_del_client(struct qmi_handle *qmi,
				unsigned int node, unsigned int port)
{
	struct qmi_ops *ops = &qmi->ops;

	if (ops->del_client)
		ops->del_client(qmi, node, port);
}