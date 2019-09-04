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
struct TYPE_2__ {int temperature; int /*<<< orphan*/  wmi_sync; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  data_lock; TYPE_1__ thermal; int /*<<< orphan*/  dev_flags; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 scalar_t__ ATH10K_STATE_ON ; 
 int /*<<< orphan*/  ATH10K_THERMAL_SYNC_TIMEOUT_HZ ; 
 int ENETDOWN ; 
 int ESHUTDOWN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_pdev_get_temperature (struct ath10k*) ; 
 struct ath10k* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ath10k_thermal_show_temp(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct ath10k *ar = dev_get_drvdata(dev);
	int ret, temperature;
	unsigned long time_left;

	mutex_lock(&ar->conf_mutex);

	/* Can't get temperature when the card is off */
	if (ar->state != ATH10K_STATE_ON) {
		ret = -ENETDOWN;
		goto out;
	}

	reinit_completion(&ar->thermal.wmi_sync);
	ret = ath10k_wmi_pdev_get_temperature(ar);
	if (ret) {
		ath10k_warn(ar, "failed to read temperature %d\n", ret);
		goto out;
	}

	if (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags)) {
		ret = -ESHUTDOWN;
		goto out;
	}

	time_left = wait_for_completion_timeout(&ar->thermal.wmi_sync,
						ATH10K_THERMAL_SYNC_TIMEOUT_HZ);
	if (!time_left) {
		ath10k_warn(ar, "failed to synchronize thermal read\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	spin_lock_bh(&ar->data_lock);
	temperature = ar->thermal.temperature;
	spin_unlock_bh(&ar->data_lock);

	/* display in millidegree celcius */
	ret = snprintf(buf, PAGE_SIZE, "%d\n", temperature * 1000);
out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}