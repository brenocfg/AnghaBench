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
struct file {int dummy; } ;
struct bcm2048_device {scalar_t__ rds_data_available; scalar_t__ rd_index; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 struct bcm2048_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int bcm2048_fops_open(struct file *file)
{
	struct bcm2048_device *bdev = video_drvdata(file);

	bdev->users++;
	bdev->rd_index = 0;
	bdev->rds_data_available = 0;

	return 0;
}