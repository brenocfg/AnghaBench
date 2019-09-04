#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {char* size; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FW_ACTION_NOHOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  async_fw_done ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,...) ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* test_firmware ; 
 int /*<<< orphan*/  test_fw_mutex ; 
 int /*<<< orphan*/  trigger_async_request_cb ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t trigger_custom_fallback_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	int rc;
	char *name;

	name = kstrndup(buf, count, GFP_KERNEL);
	if (!name)
		return -ENOSPC;

	pr_info("loading '%s' using custom fallback mechanism\n", name);

	mutex_lock(&test_fw_mutex);
	release_firmware(test_firmware);
	test_firmware = NULL;
	rc = request_firmware_nowait(THIS_MODULE, FW_ACTION_NOHOTPLUG, name,
				     dev, GFP_KERNEL, NULL,
				     trigger_async_request_cb);
	if (rc) {
		pr_info("async load of '%s' failed: %d\n", name, rc);
		kfree(name);
		goto out;
	}
	/* Free 'name' ASAP, to test for race conditions */
	kfree(name);

	wait_for_completion(&async_fw_done);

	if (test_firmware) {
		pr_info("loaded: %zu\n", test_firmware->size);
		rc = count;
	} else {
		pr_err("failed to async load firmware\n");
		rc = -ENODEV;
	}

out:
	mutex_unlock(&test_fw_mutex);

	return rc;
}