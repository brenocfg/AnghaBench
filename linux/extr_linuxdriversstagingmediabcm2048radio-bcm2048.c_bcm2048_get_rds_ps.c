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
struct TYPE_2__ {char* rds_ps; int /*<<< orphan*/  text_len; } ;
struct bcm2048_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; } ;
typedef  int /*<<< orphan*/  data_buffer ;

/* Variables and functions */
 int BCM2048_MAX_RDS_PS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_rds_ps(struct bcm2048_device *bdev, char *data)
{
	int err = 0, i, j = 0;
	char data_buffer[BCM2048_MAX_RDS_PS + 1];

	mutex_lock(&bdev->mutex);

	if (!bdev->rds_info.text_len) {
		err = -EINVAL;
		goto unlock;
	}

	for (i = 0; i < BCM2048_MAX_RDS_PS; i++) {
		if (bdev->rds_info.rds_ps[i]) {
			data_buffer[j++] = bdev->rds_info.rds_ps[i];
		} else {
			if (i < (BCM2048_MAX_RDS_PS - 1)) {
				err = -EBUSY;
				goto unlock;
			}
		}
	}

	if (j <= BCM2048_MAX_RDS_PS)
		data_buffer[j] = 0;

	memcpy(data, data_buffer, sizeof(data_buffer));

unlock:
	mutex_unlock(&bdev->mutex);
	return err;
}