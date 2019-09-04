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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ns_device_uuid_show(struct config_item *item, char *page)
{
	return sprintf(page, "%pUb\n", &to_nvmet_ns(item)->uuid);
}