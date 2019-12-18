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
struct intel_sst_drv {int /*<<< orphan*/  sst_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  firmware_name; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_cache_and_parse_fw (struct intel_sst_drv*,struct firmware const*) ; 

__attribute__((used)) static int sst_request_fw(struct intel_sst_drv *sst)
{
	int retval = 0;
	const struct firmware *fw;

	retval = request_firmware(&fw, sst->firmware_name, sst->dev);
	if (retval) {
		dev_err(sst->dev, "request fw failed %d\n", retval);
		return retval;
	}
	if (fw == NULL) {
		dev_err(sst->dev, "fw is returning as null\n");
		return -EINVAL;
	}
	mutex_lock(&sst->sst_lock);
	retval = sst_cache_and_parse_fw(sst, fw);
	mutex_unlock(&sst->sst_lock);

	return retval;
}