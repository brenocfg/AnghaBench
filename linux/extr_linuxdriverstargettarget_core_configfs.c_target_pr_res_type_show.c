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
struct se_device {int dev_reservation_flags; TYPE_1__* transport; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int transport_flags; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 int TRANSPORT_FLAG_PASSTHROUGH_PGR ; 
 struct se_device* pr_to_dev (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t target_pr_res_type_show(struct config_item *item, char *page)
{
	struct se_device *dev = pr_to_dev(item);

	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR)
		return sprintf(page, "SPC_PASSTHROUGH\n");
	else if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		return sprintf(page, "SPC2_RESERVATIONS\n");
	else
		return sprintf(page, "SPC3_PERSISTENT_RESERVATIONS\n");
}