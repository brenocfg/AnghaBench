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
struct TYPE_2__ {int hwtrap; } ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QETH_DIAGS_CMD_TRAP ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_ARM ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_CAPTURE ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_DISARM ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_hw_trap (struct qeth_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_is_diagass_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t qeth_hw_trap_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	int rc = 0;
	int state = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if (qeth_card_hw_is_reachable(card))
		state = 1;

	if (sysfs_streq(buf, "arm") && !card->info.hwtrap) {
		if (state) {
			if (qeth_is_diagass_supported(card,
			    QETH_DIAGS_CMD_TRAP)) {
				rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_ARM);
				if (!rc)
					card->info.hwtrap = 1;
			} else
				rc = -EINVAL;
		} else
			card->info.hwtrap = 1;
	} else if (sysfs_streq(buf, "disarm") && card->info.hwtrap) {
		if (state) {
			rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
			if (!rc)
				card->info.hwtrap = 0;
		} else
			card->info.hwtrap = 0;
	} else if (sysfs_streq(buf, "trap") && state && card->info.hwtrap)
		rc = qeth_hw_trap(card, QETH_DIAGS_TRAP_CAPTURE);
	else
		rc = -EINVAL;

	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}