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
struct TYPE_2__ {char* name; char* num_requests; char* read_fw_idx; scalar_t__ sync_direct; scalar_t__ into_buf; scalar_t__ send_uevent; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,...) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  test_fw_mutex ; 

__attribute__((used)) static ssize_t config_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	int len = 0;

	mutex_lock(&test_fw_mutex);

	len += scnprintf(buf, PAGE_SIZE - len,
			"Custom trigger configuration for: %s\n",
			dev_name(dev));

	if (test_fw_config->name)
		len += scnprintf(buf+len, PAGE_SIZE - len,
				"name:\t%s\n",
				test_fw_config->name);
	else
		len += scnprintf(buf+len, PAGE_SIZE - len,
				"name:\tEMTPY\n");

	len += scnprintf(buf+len, PAGE_SIZE - len,
			"num_requests:\t%u\n", test_fw_config->num_requests);

	len += scnprintf(buf+len, PAGE_SIZE - len,
			"send_uevent:\t\t%s\n",
			test_fw_config->send_uevent ?
			"FW_ACTION_HOTPLUG" :
			"FW_ACTION_NOHOTPLUG");
	len += scnprintf(buf+len, PAGE_SIZE - len,
			"into_buf:\t\t%s\n",
			test_fw_config->into_buf ? "true" : "false");
	len += scnprintf(buf+len, PAGE_SIZE - len,
			"sync_direct:\t\t%s\n",
			test_fw_config->sync_direct ? "true" : "false");
	len += scnprintf(buf+len, PAGE_SIZE - len,
			"read_fw_idx:\t%u\n", test_fw_config->read_fw_idx);

	mutex_unlock(&test_fw_mutex);

	return len;
}