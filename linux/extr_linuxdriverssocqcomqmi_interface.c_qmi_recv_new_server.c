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
struct qmi_service {unsigned int service; unsigned int version; unsigned int instance; unsigned int node; unsigned int port; int /*<<< orphan*/  list_node; } ;
struct qmi_ops {int (* new_server ) (struct qmi_handle*,struct qmi_service*) ;} ;
struct qmi_handle {int /*<<< orphan*/  lookup_results; struct qmi_ops ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct qmi_service*) ; 
 struct qmi_service* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (struct qmi_handle*,struct qmi_service*) ; 

__attribute__((used)) static void qmi_recv_new_server(struct qmi_handle *qmi,
				unsigned int service, unsigned int instance,
				unsigned int node, unsigned int port)
{
	struct qmi_ops *ops = &qmi->ops;
	struct qmi_service *svc;
	int ret;

	if (!ops->new_server)
		return;

	/* Ignore EOF marker */
	if (!node && !port)
		return;

	svc = kzalloc(sizeof(*svc), GFP_KERNEL);
	if (!svc)
		return;

	svc->service = service;
	svc->version = instance & 0xff;
	svc->instance = instance >> 8;
	svc->node = node;
	svc->port = port;

	ret = ops->new_server(qmi, svc);
	if (ret < 0)
		kfree(svc);
	else
		list_add(&svc->list_node, &qmi->lookup_results);
}