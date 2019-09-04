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
struct qmi_service {unsigned int service; unsigned int version; unsigned int instance; int /*<<< orphan*/  list_node; } ;
struct qmi_handle {int /*<<< orphan*/  lookups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qmi_service* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_send_new_lookup (struct qmi_handle*,struct qmi_service*) ; 

int qmi_add_lookup(struct qmi_handle *qmi, unsigned int service,
		   unsigned int version, unsigned int instance)
{
	struct qmi_service *svc;

	svc = kzalloc(sizeof(*svc), GFP_KERNEL);
	if (!svc)
		return -ENOMEM;

	svc->service = service;
	svc->version = version;
	svc->instance = instance;

	list_add(&svc->list_node, &qmi->lookups);

	qmi_send_new_lookup(qmi, svc);

	return 0;
}