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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;
struct nvmet_port {TYPE_1__ disc_addr; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_portid_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);
	u16 portid = 0;

	if (kstrtou16(page, 0, &portid)) {
		pr_err("Invalid value '%s' for portid\n", page);
		return -EINVAL;
	}

	if (port->enabled) {
		pr_err("Cannot modify address while enabled\n");
		pr_err("Disable the address before modifying\n");
		return -EACCES;
	}
	port->disc_addr.portid = cpu_to_le16(portid);
	return count;
}