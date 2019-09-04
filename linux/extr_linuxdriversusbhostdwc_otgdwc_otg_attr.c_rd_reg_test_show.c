#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  core_if; } ;
typedef  TYPE_1__ dwc_otg_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int MSEC_PER_JIFFIE ; 
 int RW_REG_COUNT ; 
 TYPE_1__* dwc_otg_drvdev (struct device*) ; 
 int /*<<< orphan*/  dwc_otg_get_gnptxfsiz (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  loops_per_jiffy ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t rd_reg_test_show(struct device *_dev,
				struct device_attribute *attr, char *buf)
{
        dwc_otg_device_t *otg_dev = dwc_otg_drvdev(_dev);
	int i;
	int time;
	int start_jiffies;

	printk("HZ %d, MSEC_PER_JIFFIE %d, loops_per_jiffy %lu\n",
	       HZ, MSEC_PER_JIFFIE, loops_per_jiffy);
	start_jiffies = jiffies;
	for (i = 0; i < RW_REG_COUNT; i++) {
		dwc_otg_get_gnptxfsiz(otg_dev->core_if);
	}
	time = jiffies - start_jiffies;
	return sprintf(buf,
		       "Time to read GNPTXFSIZ reg %d times: %d msecs (%d jiffies)\n",
		       RW_REG_COUNT, time * MSEC_PER_JIFFIE, time);
}