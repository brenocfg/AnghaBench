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
struct TYPE_2__ {int text_len; int* radio_text; } ;
struct bcm2048_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_MAX_RDS_RADIO_TEXT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static int bcm2048_get_rds_data(struct bcm2048_device *bdev, char *data)
{
	int err = 0, i, p = 0;
	char *data_buffer;

	mutex_lock(&bdev->mutex);

	if (!bdev->rds_info.text_len) {
		err = -EINVAL;
		goto unlock;
	}

	data_buffer = kcalloc(BCM2048_MAX_RDS_RADIO_TEXT, 5, GFP_KERNEL);
	if (!data_buffer) {
		err = -ENOMEM;
		goto unlock;
	}

	for (i = 0; i < bdev->rds_info.text_len; i++) {
		p += sprintf(data_buffer + p, "%x ",
			     bdev->rds_info.radio_text[i]);
	}

	memcpy(data, data_buffer, p);
	kfree(data_buffer);

unlock:
	mutex_unlock(&bdev->mutex);
	return err;
}