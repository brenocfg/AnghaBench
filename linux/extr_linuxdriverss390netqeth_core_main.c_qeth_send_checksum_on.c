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
typedef  int u32 ;
struct qeth_checksum_cmd {int supported; int enabled; } ;
struct qeth_card {TYPE_1__* gdev; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPA_CMD_ASS_ENABLE ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_CMD_ASS_STOP ; 
 int IPA_INBOUND_CHECKSUM ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int QETH_IPA_CHECKSUM_IP_HDR ; 
 int QETH_IPA_CHECKSUM_LP2LP ; 
 int QETH_IPA_CHECKSUM_TCP ; 
 int QETH_IPA_CHECKSUM_UDP ; 
 int QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int qeth_ipa_checksum_run_cmd (struct qeth_card*,int,int /*<<< orphan*/ ,int,struct qeth_checksum_cmd*,int) ; 
 int /*<<< orphan*/  qeth_send_simple_setassparms_prot (struct qeth_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_send_checksum_on(struct qeth_card *card, int cstype,
				 enum qeth_prot_versions prot)
{
	u32 required_features = QETH_IPA_CHECKSUM_UDP | QETH_IPA_CHECKSUM_TCP;
	struct qeth_checksum_cmd chksum_cb;
	int rc;

	if (prot == QETH_PROT_IPV4)
		required_features |= QETH_IPA_CHECKSUM_IP_HDR;
	rc = qeth_ipa_checksum_run_cmd(card, cstype, IPA_CMD_ASS_START, 0,
				       &chksum_cb, prot);
	if (!rc) {
		if ((required_features & chksum_cb.supported) !=
		    required_features)
			rc = -EIO;
		else if (!(QETH_IPA_CHECKSUM_LP2LP & chksum_cb.supported) &&
			 cstype == IPA_INBOUND_CHECKSUM)
			dev_warn(&card->gdev->dev,
				 "Hardware checksumming is performed only if %s and its peer use different OSA Express 3 ports\n",
				 QETH_CARD_IFNAME(card));
	}
	if (rc) {
		qeth_send_simple_setassparms_prot(card, cstype,
						  IPA_CMD_ASS_STOP, 0, prot);
		dev_warn(&card->gdev->dev,
			 "Starting HW IPv%d checksumming for %s failed, using SW checksumming\n",
			 prot, QETH_CARD_IFNAME(card));
		return rc;
	}
	rc = qeth_ipa_checksum_run_cmd(card, cstype, IPA_CMD_ASS_ENABLE,
				       chksum_cb.supported, &chksum_cb,
				       prot);
	if (!rc) {
		if ((required_features & chksum_cb.enabled) !=
		    required_features)
			rc = -EIO;
	}
	if (rc) {
		qeth_send_simple_setassparms_prot(card, cstype,
						  IPA_CMD_ASS_STOP, 0, prot);
		dev_warn(&card->gdev->dev,
			 "Enabling HW IPv%d checksumming for %s failed, using SW checksumming\n",
			 prot, QETH_CARD_IFNAME(card));
		return rc;
	}

	dev_info(&card->gdev->dev, "HW Checksumming (%sbound IPv%d) enabled\n",
		 cstype == IPA_INBOUND_CHECKSUM ? "in" : "out", prot);
	return 0;
}