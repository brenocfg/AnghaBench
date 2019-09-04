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
struct qeth_card {TYPE_1__* gdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ssize_t qeth_dev_portname_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);

	dev_warn_once(&card->gdev->dev,
		      "portname is deprecated and is ignored\n");
	return count;
}