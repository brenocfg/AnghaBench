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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  test_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_dev_config_show_int (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static ssize_t test_result_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	return test_dev_config_show_int(buf, test_fw_config->test_result);
}