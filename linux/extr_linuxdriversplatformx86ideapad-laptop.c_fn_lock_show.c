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
struct ideapad_private {TYPE_1__* adev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  HA_FNLOCK_BIT ; 
 struct ideapad_private* dev_get_drvdata (struct device*) ; 
 int read_method_int (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t fn_lock_show(struct device *dev,
			    struct device_attribute *attr,
			    char *buf)
{
	struct ideapad_private *priv = dev_get_drvdata(dev);
	unsigned long result;
	int hals;
	int fail = read_method_int(priv->adev->handle, "HALS", &hals);

	if (fail)
		return sprintf(buf, "-1\n");

	result = hals;
	return sprintf(buf, "%u\n", test_bit(HA_FNLOCK_BIT, &result));
}