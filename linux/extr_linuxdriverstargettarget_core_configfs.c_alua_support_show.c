#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct se_dev_attrib {TYPE_2__* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* transport; } ;
struct TYPE_3__ {int transport_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TRANSPORT_FLAG_PASSTHROUGH_ALUA ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t alua_support_show(struct config_item *item, char *page)
{
	struct se_dev_attrib *da = to_attrib(item);
	u8 flags = da->da_dev->transport->transport_flags;

	return snprintf(page, PAGE_SIZE, "%d\n",
			flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ? 0 : 1);
}