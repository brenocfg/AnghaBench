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
struct TYPE_2__ {char* unit_serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* to_t10_wwn (struct config_item*) ; 

__attribute__((used)) static ssize_t target_wwn_vpd_unit_serial_show(struct config_item *item,
		char *page)
{
	return sprintf(page, "T10 VPD Unit Serial Number: %s\n",
		&to_t10_wwn(item)->unit_serial[0]);
}