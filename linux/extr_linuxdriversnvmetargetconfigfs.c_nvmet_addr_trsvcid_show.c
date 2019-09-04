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
struct TYPE_2__ {char* trsvcid; } ;
struct nvmet_port {TYPE_1__ disc_addr; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_trsvcid_show(struct config_item *item,
		char *page)
{
	struct nvmet_port *port = to_nvmet_port(item);

	return snprintf(page, PAGE_SIZE, "%s\n",
			port->disc_addr.trsvcid);
}