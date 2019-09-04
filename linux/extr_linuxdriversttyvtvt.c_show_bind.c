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
struct con_driver {int /*<<< orphan*/  con; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int con_is_bound (int /*<<< orphan*/ ) ; 
 struct con_driver* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_bind(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct con_driver *con = dev_get_drvdata(dev);
	int bind = con_is_bound(con->con);

	return snprintf(buf, PAGE_SIZE, "%i\n", bind);
}