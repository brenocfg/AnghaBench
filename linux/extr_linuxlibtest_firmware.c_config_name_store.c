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
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __kstrncpy (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  test_fw_mutex ; 

__attribute__((used)) static ssize_t config_name_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	int ret;

	mutex_lock(&test_fw_mutex);
	kfree_const(test_fw_config->name);
	ret = __kstrncpy(&test_fw_config->name, buf, count, GFP_KERNEL);
	mutex_unlock(&test_fw_mutex);

	return ret;
}