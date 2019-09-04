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
struct nfc_digital_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* tg_configure_hw ) (struct nfc_digital_dev*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int stub1 (struct nfc_digital_dev*,int,int) ; 

int digital_tg_configure_hw(struct nfc_digital_dev *ddev, int type, int param)
{
	int rc;

	rc = ddev->ops->tg_configure_hw(ddev, type, param);
	if (rc)
		pr_err("tg_configure_hw failed: %d\n", rc);

	return rc;
}