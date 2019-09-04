#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ trtype; int /*<<< orphan*/  tsas; } ;
struct nvmet_port {TYPE_1__ disc_addr; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 scalar_t__ NVMF_TRTYPE_RDMA ; 
 int /*<<< orphan*/  NVMF_TSAS_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_port_init_tsas_rdma (struct nvmet_port*) ; 
 TYPE_2__* nvmet_transport_names ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_trtype_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);
	int i;

	if (port->enabled) {
		pr_err("Cannot modify address while enabled\n");
		pr_err("Disable the address before modifying\n");
		return -EACCES;
	}

	for (i = 0; i < ARRAY_SIZE(nvmet_transport_names); i++) {
		if (sysfs_streq(page, nvmet_transport_names[i].name))
			goto found;
	}

	pr_err("Invalid value '%s' for trtype\n", page);
	return -EINVAL;
found:
	memset(&port->disc_addr.tsas, 0, NVMF_TSAS_SIZE);
	port->disc_addr.trtype = nvmet_transport_names[i].type;
	if (port->disc_addr.trtype == NVMF_TRTYPE_RDMA)
		nvmet_port_init_tsas_rdma(port);
	return count;
}