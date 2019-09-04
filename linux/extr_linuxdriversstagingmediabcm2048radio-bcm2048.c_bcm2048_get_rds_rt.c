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
struct TYPE_2__ {int* rds_rt; int /*<<< orphan*/  text_len; } ;
struct bcm2048_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; } ;
typedef  int /*<<< orphan*/  data_buffer ;

/* Variables and functions */
 int BCM2048_MAX_RDS_RT ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_rds_rt(struct bcm2048_device *bdev, char *data)
{
	int err = 0, i, j = 0, ce = 0, cr = 0;
	char data_buffer[BCM2048_MAX_RDS_RT + 1];

	mutex_lock(&bdev->mutex);

	if (!bdev->rds_info.text_len) {
		err = -EINVAL;
		goto unlock;
	}

	for (i = 0; i < BCM2048_MAX_RDS_RT; i++) {
		if (bdev->rds_info.rds_rt[i]) {
			ce = i;
			/* Skip the carriage return */
			if (bdev->rds_info.rds_rt[i] != 0x0d) {
				data_buffer[j++] = bdev->rds_info.rds_rt[i];
			} else {
				cr = i;
				break;
			}
		}
	}

	if (j <= BCM2048_MAX_RDS_RT)
		data_buffer[j] = 0;

	for (i = 0; i < BCM2048_MAX_RDS_RT; i++) {
		if (!bdev->rds_info.rds_rt[i]) {
			if (cr && (i < cr)) {
				err = -EBUSY;
				goto unlock;
			}
			if (i < ce) {
				if (cr && (i >= cr))
					break;
				err = -EBUSY;
				goto unlock;
			}
		}
	}

	memcpy(data, data_buffer, sizeof(data_buffer));

unlock:
	mutex_unlock(&bdev->mutex);
	return err;
}