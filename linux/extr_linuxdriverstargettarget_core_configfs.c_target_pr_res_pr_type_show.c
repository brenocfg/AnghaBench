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
struct t10_pr_registration {int /*<<< orphan*/  pr_res_type; } ;
struct se_device {int /*<<< orphan*/  dev_reservation_lock; struct t10_pr_registration* dev_pr_res_holder; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* core_scsi3_pr_dump_type (int /*<<< orphan*/ ) ; 
 struct se_device* pr_to_dev (struct config_item*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t target_pr_res_pr_type_show(struct config_item *item, char *page)
{
	struct se_device *dev = pr_to_dev(item);
	struct t10_pr_registration *pr_reg;
	ssize_t len = 0;

	spin_lock(&dev->dev_reservation_lock);
	pr_reg = dev->dev_pr_res_holder;
	if (pr_reg) {
		len = sprintf(page, "SPC-3 Reservation Type: %s\n",
			core_scsi3_pr_dump_type(pr_reg->pr_res_type));
	} else {
		len = sprintf(page, "No SPC-3 Reservation holder\n");
	}

	spin_unlock(&dev->dev_reservation_lock);
	return len;
}