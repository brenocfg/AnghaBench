#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  text_len; int /*<<< orphan*/  radio_text; } ;
struct bcm2048_device {int /*<<< orphan*/  read_queue; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fifo_size; TYPE_2__ rds_info; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_RDS_DATA ; 
 int /*<<< orphan*/  bcm2048_parse_rds_pi (struct bcm2048_device*) ; 
 int /*<<< orphan*/  bcm2048_parse_rds_ps (struct bcm2048_device*) ; 
 int /*<<< orphan*/  bcm2048_parse_rds_rt (struct bcm2048_device*) ; 
 int bcm2048_recv_duples (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2048_rds_fifo_receive(struct bcm2048_device *bdev)
{
	int err;

	mutex_lock(&bdev->mutex);

	err = bcm2048_recv_duples(bdev, BCM2048_I2C_RDS_DATA,
				  bdev->rds_info.radio_text, bdev->fifo_size);
	if (err != 2) {
		dev_err(&bdev->client->dev, "RDS Read problem\n");
		mutex_unlock(&bdev->mutex);
		return;
	}

	bdev->rds_info.text_len = bdev->fifo_size;

	bcm2048_parse_rds_pi(bdev);
	bcm2048_parse_rds_rt(bdev);
	bcm2048_parse_rds_ps(bdev);

	mutex_unlock(&bdev->mutex);

	wake_up_interruptible(&bdev->read_queue);
}