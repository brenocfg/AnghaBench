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
struct TYPE_2__ {int /*<<< orphan*/  read_fw_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_dev_config_update_u8 (char const*,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static ssize_t config_read_fw_idx_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	return test_dev_config_update_u8(buf, count,
					 &test_fw_config->read_fw_idx);
}