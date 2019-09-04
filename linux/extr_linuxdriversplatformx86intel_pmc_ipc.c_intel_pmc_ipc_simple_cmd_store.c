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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int intel_pmc_ipc_simple_command (int,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static ssize_t intel_pmc_ipc_simple_cmd_store(struct device *dev,
					      struct device_attribute *attr,
					      const char *buf, size_t count)
{
	int subcmd;
	int cmd;
	int ret;

	ret = sscanf(buf, "%d %d", &cmd, &subcmd);
	if (ret != 2) {
		dev_err(dev, "Error args\n");
		return -EINVAL;
	}

	ret = intel_pmc_ipc_simple_command(cmd, subcmd);
	if (ret) {
		dev_err(dev, "command %d error with %d\n", cmd, ret);
		return ret;
	}
	return (ssize_t)count;
}