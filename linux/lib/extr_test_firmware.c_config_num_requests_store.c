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
struct TYPE_2__ {int /*<<< orphan*/  num_requests; scalar_t__ reqs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int test_dev_config_update_u8 (char const*,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  test_fw_mutex ; 

__attribute__((used)) static ssize_t config_num_requests_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	int rc;

	mutex_lock(&test_fw_mutex);
	if (test_fw_config->reqs) {
		pr_err("Must call release_all_firmware prior to changing config\n");
		rc = -EINVAL;
		mutex_unlock(&test_fw_mutex);
		goto out;
	}
	mutex_unlock(&test_fw_mutex);

	rc = test_dev_config_update_u8(buf, count,
				       &test_fw_config->num_requests);

out:
	return rc;
}