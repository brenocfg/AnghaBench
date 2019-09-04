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
struct s3fwrn5_i2c_phy {int /*<<< orphan*/  mutex; int /*<<< orphan*/  gpio_fw_wake; } ;

/* Variables and functions */
 int S3FWRN5_EN_WAIT_TIME ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3fwrn5_i2c_set_wake(void *phy_id, bool wake)
{
	struct s3fwrn5_i2c_phy *phy = phy_id;

	mutex_lock(&phy->mutex);
	gpio_set_value(phy->gpio_fw_wake, wake);
	msleep(S3FWRN5_EN_WAIT_TIME/2);
	mutex_unlock(&phy->mutex);
}