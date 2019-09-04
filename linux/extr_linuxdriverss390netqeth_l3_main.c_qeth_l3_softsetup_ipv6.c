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
struct TYPE_4__ {scalar_t__ type; } ;
struct qeth_card {TYPE_1__* gdev; TYPE_2__ info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_IPV6 ; 
 int /*<<< orphan*/  IPA_PASSTHRU ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int qeth_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qeth_send_simple_setassparms_v6 (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_softsetup_ipv6(struct qeth_card *card)
{
	int rc;

	QETH_CARD_TEXT(card, 3, "softipv6");

	if (card->info.type == QETH_CARD_TYPE_IQD)
		goto out;

	rc = qeth_send_simple_setassparms(card, IPA_IPV6,
					  IPA_CMD_ASS_START, 3);
	if (rc) {
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			QETH_CARD_IFNAME(card));
		return rc;
	}
	rc = qeth_send_simple_setassparms_v6(card, IPA_IPV6,
					     IPA_CMD_ASS_START, 0);
	if (rc) {
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			 QETH_CARD_IFNAME(card));
		return rc;
	}
	rc = qeth_send_simple_setassparms_v6(card, IPA_PASSTHRU,
					     IPA_CMD_ASS_START, 0);
	if (rc) {
		dev_warn(&card->gdev->dev,
			"Enabling the passthrough mode for %s failed\n",
			QETH_CARD_IFNAME(card));
		return rc;
	}
out:
	dev_info(&card->gdev->dev, "IPV6 enabled\n");
	return 0;
}