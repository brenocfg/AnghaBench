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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_waiting; } ;
struct cuse_conn {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct cuse_conn* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t cuse_class_waiting_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct cuse_conn *cc = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", atomic_read(&cc->fc.num_waiting));
}