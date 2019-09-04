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
struct osst_tape {int first_data_ppos; scalar_t__ linux_media; scalar_t__ header_ok; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t osst_first_data_ppos_show(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct osst_tape * STp = (struct osst_tape *) dev_get_drvdata (dev);
	ssize_t l = 0;

	if (STp && STp->header_ok && STp->linux_media)
		l = snprintf(buf, PAGE_SIZE, "%d\n", STp->first_data_ppos);
	return l;
}