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
struct s3fwrn5_i2c_phy {int mode; int /*<<< orphan*/  mutex; scalar_t__ irq_skip; int /*<<< orphan*/  ndev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  S3FWRN5_MODE_COLD 130 
#define  S3FWRN5_MODE_FW 129 
#define  S3FWRN5_MODE_NCI 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s3fwrn5_i2c_read (struct s3fwrn5_i2c_phy*) ; 

__attribute__((used)) static irqreturn_t s3fwrn5_i2c_irq_thread_fn(int irq, void *phy_id)
{
	struct s3fwrn5_i2c_phy *phy = phy_id;
	int ret = 0;

	if (!phy || !phy->ndev) {
		WARN_ON_ONCE(1);
		return IRQ_NONE;
	}

	mutex_lock(&phy->mutex);

	if (phy->irq_skip)
		goto out;

	switch (phy->mode) {
	case S3FWRN5_MODE_NCI:
	case S3FWRN5_MODE_FW:
		ret = s3fwrn5_i2c_read(phy);
		break;
	case S3FWRN5_MODE_COLD:
		ret = -EREMOTEIO;
		break;
	}

out:
	mutex_unlock(&phy->mutex);

	return IRQ_HANDLED;
}