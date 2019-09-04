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
struct TYPE_2__ {scalar_t__ type; scalar_t__ major; scalar_t__ minor; scalar_t__ build; } ;
struct intel_sst_drv {TYPE_1__ fw_version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t firmware_version_show(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	if (ctx->fw_version.type == 0 && ctx->fw_version.major == 0 &&
	    ctx->fw_version.minor == 0 && ctx->fw_version.build == 0)
		return sprintf(buf, "FW not yet loaded\n");
	else
		return sprintf(buf, "v%02x.%02x.%02x.%02x\n",
			       ctx->fw_version.type, ctx->fw_version.major,
			       ctx->fw_version.minor, ctx->fw_version.build);

}