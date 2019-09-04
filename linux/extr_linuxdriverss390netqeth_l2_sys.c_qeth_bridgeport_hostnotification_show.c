#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hostnotification; } ;
struct TYPE_4__ {TYPE_1__ sbp; } ;
struct qeth_card {TYPE_2__ options; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 scalar_t__ qeth_l2_vnicc_is_in_use (struct qeth_card*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t qeth_bridgeport_hostnotification_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	int enabled;

	if (!card)
		return -EINVAL;

	if (qeth_l2_vnicc_is_in_use(card))
		return sprintf(buf, "n/a (VNIC characteristics)\n");

	enabled = card->options.sbp.hostnotification;

	return sprintf(buf, "%d\n", enabled);
}