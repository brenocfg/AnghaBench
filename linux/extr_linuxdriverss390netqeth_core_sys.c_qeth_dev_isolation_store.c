#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int prev_isolation; int isolation; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_3__ options; TYPE_2__* gdev; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum qeth_ipa_isolation_modes { ____Placeholder_qeth_ipa_isolation_modes } qeth_ipa_isolation_modes ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_QETH_ISOLATION_DROP ; 
 int /*<<< orphan*/  ATTR_QETH_ISOLATION_FWD ; 
 int /*<<< orphan*/  ATTR_QETH_ISOLATION_NONE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ISOLATION_MODE_DROP ; 
 int ISOLATION_MODE_FWD ; 
 int ISOLATION_MODE_NONE ; 
 scalar_t__ QETH_CARD_TYPE_OSD ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_set_access_ctrl_online (struct qeth_card*,int) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qeth_dev_isolation_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	enum qeth_ipa_isolation_modes isolation;
	int rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if (card->info.type != QETH_CARD_TYPE_OSD &&
	    card->info.type != QETH_CARD_TYPE_OSX) {
		rc = -EOPNOTSUPP;
		dev_err(&card->gdev->dev, "Adapter does not "
			"support QDIO data connection isolation\n");
		goto out;
	}

	/* parse input into isolation mode */
	if (sysfs_streq(buf, ATTR_QETH_ISOLATION_NONE)) {
		isolation = ISOLATION_MODE_NONE;
	} else if (sysfs_streq(buf, ATTR_QETH_ISOLATION_FWD)) {
		isolation = ISOLATION_MODE_FWD;
	} else if (sysfs_streq(buf, ATTR_QETH_ISOLATION_DROP)) {
		isolation = ISOLATION_MODE_DROP;
	} else {
		rc = -EINVAL;
		goto out;
	}
	rc = count;

	/* defer IP assist if device is offline (until discipline->set_online)*/
	card->options.prev_isolation = card->options.isolation;
	card->options.isolation = isolation;
	if (qeth_card_hw_is_reachable(card)) {
		int ipa_rc = qeth_set_access_ctrl_online(card, 1);
		if (ipa_rc != 0)
			rc = ipa_rc;
	}
out:
	mutex_unlock(&card->conf_mutex);
	return rc;
}