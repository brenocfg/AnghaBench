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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_CMD_ASS_STOP ; 
 int /*<<< orphan*/  IPA_OUTBOUND_TSO ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int qeth_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_set_ipa_tso(struct qeth_card *card, int on)
{
	int rc;

	QETH_CARD_TEXT(card, 3, "sttso");

	if (on) {
		rc = qeth_send_simple_setassparms(card, IPA_OUTBOUND_TSO,
						  IPA_CMD_ASS_START, 0);
		if (rc) {
			dev_warn(&card->gdev->dev,
				 "Starting outbound TCP segmentation offload for %s failed\n",
				 QETH_CARD_IFNAME(card));
			return -EIO;
		}
		dev_info(&card->gdev->dev, "Outbound TSO enabled\n");
	} else {
		rc = qeth_send_simple_setassparms(card, IPA_OUTBOUND_TSO,
						  IPA_CMD_ASS_STOP, 0);
	}
	return rc;
}