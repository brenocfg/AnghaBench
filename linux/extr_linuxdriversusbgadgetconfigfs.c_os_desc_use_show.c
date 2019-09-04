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
struct TYPE_2__ {int use_os_desc; } ;

/* Variables and functions */
 TYPE_1__* os_desc_item_to_gadget_info (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t os_desc_use_show(struct config_item *item, char *page)
{
	return sprintf(page, "%d\n",
			os_desc_item_to_gadget_info(item)->use_os_desc);
}