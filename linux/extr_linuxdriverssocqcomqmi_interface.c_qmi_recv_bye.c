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
struct qmi_ops {int /*<<< orphan*/  (* bye ) (struct qmi_handle*,unsigned int) ;} ;
struct qmi_handle {struct qmi_ops ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  qmi_recv_del_server (struct qmi_handle*,unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (struct qmi_handle*,unsigned int) ; 

__attribute__((used)) static void qmi_recv_bye(struct qmi_handle *qmi,
			 unsigned int node)
{
	struct qmi_ops *ops = &qmi->ops;

	qmi_recv_del_server(qmi, node, -1);

	if (ops->bye)
		ops->bye(qmi, node);
}