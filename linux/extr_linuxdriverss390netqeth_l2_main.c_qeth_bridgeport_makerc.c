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
struct TYPE_3__ {scalar_t__ type; } ;
struct qeth_card {TYPE_2__* gdev; TYPE_1__ info; } ;
struct _qeth_sbp_cbctl {scalar_t__ ipa_rc; scalar_t__ cmd_rc; } ;
typedef  enum qeth_ipa_sbp_cmd { ____Placeholder_qeth_ipa_sbp_cmd } qeth_ipa_sbp_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EEXIST ; 
 int EIO ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  IPA_RC_L2_UNSUPPORTED_CMD 147 
#define  IPA_RC_NOTSUPP 146 
#define  IPA_RC_SBP_IQD_ANO_DEV_PRIMARY 145 
#define  IPA_RC_SBP_IQD_CURRENT_PRIMARY 144 
#define  IPA_RC_SBP_IQD_CURRENT_SECOND 143 
#define  IPA_RC_SBP_IQD_LIMIT_SECOND 142 
#define  IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN 141 
#define  IPA_RC_SBP_IQD_NOT_CONFIGURED 140 
#define  IPA_RC_SBP_IQD_OS_MISMATCH 139 
#define  IPA_RC_SBP_OSA_ANO_DEV_PRIMARY 138 
#define  IPA_RC_SBP_OSA_CURRENT_PRIMARY 137 
#define  IPA_RC_SBP_OSA_CURRENT_SECOND 136 
#define  IPA_RC_SBP_OSA_LIMIT_SECOND 135 
#define  IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN 134 
#define  IPA_RC_SBP_OSA_NOT_CONFIGURED 133 
#define  IPA_RC_SBP_OSA_OS_MISMATCH 132 
#define  IPA_RC_SUCCESS 131 
#define  IPA_RC_UNSUPPORTED_COMMAND 130 
#define  IPA_SBP_SET_PRIMARY_BRIDGE_PORT 129 
#define  IPA_SBP_SET_SECONDARY_BRIDGE_PORT 128 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,scalar_t__) ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int qeth_bridgeport_makerc(struct qeth_card *card,
	struct _qeth_sbp_cbctl *cbctl, enum qeth_ipa_sbp_cmd setcmd)
{
	int rc;
	int is_iqd = (card->info.type == QETH_CARD_TYPE_IQD);

	if ((is_iqd && (cbctl->ipa_rc == IPA_RC_SUCCESS)) ||
	    (!is_iqd && (cbctl->ipa_rc == cbctl->cmd_rc)))
		switch (cbctl->cmd_rc) {
		case IPA_RC_SUCCESS:
			rc = 0;
			break;
		case IPA_RC_L2_UNSUPPORTED_CMD:
		case IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			break;
		case IPA_RC_SBP_OSA_NOT_CONFIGURED:
		case IPA_RC_SBP_IQD_NOT_CONFIGURED:
			rc = -ENODEV; /* maybe not the best code here? */
			dev_err(&card->gdev->dev,
	"The device is not configured as a Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_OS_MISMATCH:
		case IPA_RC_SBP_IQD_OS_MISMATCH:
			rc = -EPERM;
			dev_err(&card->gdev->dev,
	"A Bridge Port is already configured by a different operating system\n");
			break;
		case IPA_RC_SBP_OSA_ANO_DEV_PRIMARY:
		case IPA_RC_SBP_IQD_ANO_DEV_PRIMARY:
			switch (setcmd) {
			case IPA_SBP_SET_PRIMARY_BRIDGE_PORT:
				rc = -EEXIST;
				dev_err(&card->gdev->dev,
	"The LAN already has a primary Bridge Port\n");
				break;
			case IPA_SBP_SET_SECONDARY_BRIDGE_PORT:
				rc = -EBUSY;
				dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
				break;
			default:
				rc = -EIO;
			}
			break;
		case IPA_RC_SBP_OSA_CURRENT_SECOND:
		case IPA_RC_SBP_IQD_CURRENT_SECOND:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a secondary Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_LIMIT_SECOND:
		case IPA_RC_SBP_IQD_LIMIT_SECOND:
			rc = -EEXIST;
			dev_err(&card->gdev->dev,
	"The LAN cannot have more secondary Bridge Ports\n");
			break;
		case IPA_RC_SBP_OSA_CURRENT_PRIMARY:
		case IPA_RC_SBP_IQD_CURRENT_PRIMARY:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN:
		case IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN:
			rc = -EACCES;
			dev_err(&card->gdev->dev,
	"The device is not authorized to be a Bridge Port\n");
			break;
		default:
			rc = -EIO;
		}
	else
		switch (cbctl->ipa_rc) {
		case IPA_RC_NOTSUPP:
			rc = -EOPNOTSUPP;
			break;
		case IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			break;
		default:
			rc = -EIO;
		}

	if (rc) {
		QETH_CARD_TEXT_(card, 2, "SBPi%04x", cbctl->ipa_rc);
		QETH_CARD_TEXT_(card, 2, "SBPc%04x", cbctl->cmd_rc);
	}
	return rc;
}