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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l2_vnicc_set_state (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_sysfs_attr_to_char (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qeth_vnicc_char_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	bool state;
	u32 vnicc;
	int rc;

	if (!card)
		return -EINVAL;

	if (kstrtobool(buf, &state))
		return -EINVAL;

	vnicc = qeth_l2_vnicc_sysfs_attr_to_char(attr->attr.name);
	mutex_lock(&card->conf_mutex);
	rc = qeth_l2_vnicc_set_state(card, vnicc, state);
	mutex_unlock(&card->conf_mutex);

	return rc ? rc : count;
}