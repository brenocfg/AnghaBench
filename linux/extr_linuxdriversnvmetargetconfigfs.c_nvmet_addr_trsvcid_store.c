#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  trsvcid; } ;
struct nvmet_port {TYPE_1__ disc_addr; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EINVAL ; 
 size_t NVMF_TRSVCID_SIZE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ ) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_trsvcid_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);

	if (count > NVMF_TRSVCID_SIZE) {
		pr_err("Invalid value '%s' for trsvcid\n", page);
		return -EINVAL;
	}
	if (port->enabled) {
		pr_err("Cannot modify address while enabled\n");
		pr_err("Disable the address before modifying\n");
		return -EACCES;
	}

	if (sscanf(page, "%s\n", port->disc_addr.trsvcid) != 1)
		return -EINVAL;
	return count;
}