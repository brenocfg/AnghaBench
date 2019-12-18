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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cuse_conn {int /*<<< orphan*/  fc; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct cuse_conn* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fuse_abort_conn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t cuse_class_abort_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct cuse_conn *cc = dev_get_drvdata(dev);

	fuse_abort_conn(&cc->fc);
	return count;
}