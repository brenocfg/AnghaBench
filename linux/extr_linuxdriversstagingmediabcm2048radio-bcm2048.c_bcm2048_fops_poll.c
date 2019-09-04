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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
struct bcm2048_device {scalar_t__ rds_data_available; int /*<<< orphan*/  read_queue; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 struct bcm2048_device* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t bcm2048_fops_poll(struct file *file,
				  struct poll_table_struct *pts)
{
	struct bcm2048_device *bdev = video_drvdata(file);
	__poll_t retval = 0;

	poll_wait(file, &bdev->read_queue, pts);

	if (bdev->rds_data_available)
		retval = EPOLLIN | EPOLLRDNORM;

	return retval;
}