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
struct rw_semaphore {int dummy; } ;
struct fsg_lun {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct rw_semaphore* dev_get_drvdata (struct device*) ; 
 struct fsg_lun* fsg_lun_from_dev (struct device*) ; 
 int /*<<< orphan*/  fsg_show_file (struct fsg_lun*,struct rw_semaphore*,char*) ; 

__attribute__((used)) static ssize_t file_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct fsg_lun		*curlun = fsg_lun_from_dev(dev);
	struct rw_semaphore	*filesem = dev_get_drvdata(dev);

	return fsg_show_file(curlun, filesem, buf);
}