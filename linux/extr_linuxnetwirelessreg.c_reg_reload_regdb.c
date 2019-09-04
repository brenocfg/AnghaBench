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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* reg_pdev ; 
 void* regdb ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  valid_regdb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int reg_reload_regdb(void)
{
	const struct firmware *fw;
	void *db;
	int err;

	err = request_firmware(&fw, "regulatory.db", &reg_pdev->dev);
	if (err)
		return err;

	if (!valid_regdb(fw->data, fw->size)) {
		err = -ENODATA;
		goto out;
	}

	db = kmemdup(fw->data, fw->size, GFP_KERNEL);
	if (!db) {
		err = -ENOMEM;
		goto out;
	}

	rtnl_lock();
	if (!IS_ERR_OR_NULL(regdb))
		kfree(regdb);
	regdb = db;
	rtnl_unlock();

 out:
	release_firmware(fw);
	return err;
}