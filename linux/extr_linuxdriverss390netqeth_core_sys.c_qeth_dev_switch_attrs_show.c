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
struct qeth_switch_info {int capabilities; int settings; } ;
struct qeth_card {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int QETH_SWITCH_FORW_802_1 ; 
 int QETH_SWITCH_FORW_REFL_RELAY ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int qeth_query_switch_attributes (struct qeth_card*,struct qeth_switch_info*) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t qeth_dev_switch_attrs_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	struct qeth_switch_info sw_info;
	int	rc = 0;

	if (!card)
		return -EINVAL;

	if (!qeth_card_hw_is_reachable(card))
		return sprintf(buf, "n/a\n");

	rc = qeth_query_switch_attributes(card, &sw_info);
	if (rc)
		return rc;

	if (!sw_info.capabilities)
		rc = sprintf(buf, "unknown");

	if (sw_info.capabilities & QETH_SWITCH_FORW_802_1)
		rc = sprintf(buf, (sw_info.settings & QETH_SWITCH_FORW_802_1 ?
							"[802.1]" : "802.1"));
	if (sw_info.capabilities & QETH_SWITCH_FORW_REFL_RELAY)
		rc += sprintf(buf + rc,
			(sw_info.settings & QETH_SWITCH_FORW_REFL_RELAY ?
							" [rr]" : " rr"));
	rc += sprintf(buf + rc, "\n");

	return rc;
}