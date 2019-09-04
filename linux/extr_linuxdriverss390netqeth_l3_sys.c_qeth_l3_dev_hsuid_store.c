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
struct TYPE_6__ {scalar_t__ cq; char* hsuid; scalar_t__ sniffer; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct qeth_card {scalar_t__ state; TYPE_3__ options; TYPE_2__* dev; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_CQ_DISABLED ; 
 int /*<<< orphan*/  QETH_CQ_ENABLED ; 
 scalar_t__ QETH_CQ_NOTAVAILABLE ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ qeth_configure_cq (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_modify_hsuid (struct qeth_card*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_hsuid_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int rc;

	if (!card)
		return -EINVAL;

	if (card->info.type != QETH_CARD_TYPE_IQD)
		return -EPERM;
	if (card->state != CARD_STATE_DOWN &&
	    card->state != CARD_STATE_RECOVER)
		return -EPERM;
	if (card->options.sniffer)
		return -EPERM;
	if (card->options.cq == QETH_CQ_NOTAVAILABLE)
		return -EPERM;

	tmp = strsep((char **)&buf, "\n");
	if (strlen(tmp) > 8)
		return -EINVAL;

	if (card->options.hsuid[0])
		/* delete old ip address */
		qeth_l3_modify_hsuid(card, false);

	if (strlen(tmp) == 0) {
		/* delete ip address only */
		card->options.hsuid[0] = '\0';
		memcpy(card->dev->perm_addr, card->options.hsuid, 9);
		qeth_configure_cq(card, QETH_CQ_DISABLED);
		return count;
	}

	if (qeth_configure_cq(card, QETH_CQ_ENABLED))
		return -EPERM;

	snprintf(card->options.hsuid, sizeof(card->options.hsuid),
		 "%-8s", tmp);
	ASCEBC(card->options.hsuid, 8);
	memcpy(card->dev->perm_addr, card->options.hsuid, 9);

	rc = qeth_l3_modify_hsuid(card, true);

	return rc ? rc : count;
}