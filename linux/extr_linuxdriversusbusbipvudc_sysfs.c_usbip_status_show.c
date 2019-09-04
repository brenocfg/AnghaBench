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
struct TYPE_2__ {int status; int /*<<< orphan*/  lock; } ;
struct vudc {TYPE_1__ ud; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t usbip_status_show(struct device *dev,
			       struct device_attribute *attr, char *out)
{
	struct vudc *udc = (struct vudc *) dev_get_drvdata(dev);
	int status;

	if (!udc) {
		dev_err(dev, "no device");
		return -ENODEV;
	}
	spin_lock_irq(&udc->ud.lock);
	status = udc->ud.status;
	spin_unlock_irq(&udc->ud.lock);

	return snprintf(out, PAGE_SIZE, "%d\n", status);
}