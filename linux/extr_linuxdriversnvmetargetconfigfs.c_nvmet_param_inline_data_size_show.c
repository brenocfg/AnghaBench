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
struct nvmet_port {int inline_data_size; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_param_inline_data_size_show(struct config_item *item,
		char *page)
{
	struct nvmet_port *port = to_nvmet_port(item);

	return snprintf(page, PAGE_SIZE, "%d\n", port->inline_data_size);
}