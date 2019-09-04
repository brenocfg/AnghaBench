#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct qeth_set_access_ctrl {int /*<<< orphan*/  subcmd_code; } ;
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_16__ {int return_code; } ;
struct TYPE_14__ {struct qeth_set_access_ctrl set_access_ctrl; } ;
struct TYPE_17__ {TYPE_4__ hdr; TYPE_2__ data; } ;
struct TYPE_18__ {TYPE_5__ setadapterparms; } ;
struct TYPE_13__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_6__ data; TYPE_1__ hdr; } ;
struct TYPE_20__ {int /*<<< orphan*/  prev_isolation; int /*<<< orphan*/  isolation; } ;
struct qeth_card {TYPE_8__ options; TYPE_7__* gdev; } ;
struct TYPE_15__ {int name; } ;
struct TYPE_21__ {TYPE_3__ kobj; } ;
struct TYPE_19__ {TYPE_9__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISOLATION_MODE_NONE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,...) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  SETUP ; 
#define  SET_ACCESS_CTRL_RC_ACTIVE_CHECKSUM_OFF 136 
#define  SET_ACCESS_CTRL_RC_ALREADY_ISOLATED 135 
#define  SET_ACCESS_CTRL_RC_ALREADY_NOT_ISOLATED 134 
#define  SET_ACCESS_CTRL_RC_NONE_SHARED_ADAPTER 133 
#define  SET_ACCESS_CTRL_RC_NOT_SUPPORTED 132 
#define  SET_ACCESS_CTRL_RC_REFLREL_DEACT_FAILED 131 
#define  SET_ACCESS_CTRL_RC_REFLREL_FAILED 130 
#define  SET_ACCESS_CTRL_RC_REFLREL_UNSUPPORTED 129 
#define  SET_ACCESS_CTRL_RC_SUCCESS 128 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_9__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  qeth_setadpparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_setadpparms_set_access_ctrl_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_set_access_ctrl *access_ctrl_req;
	int fallback = *(int *)reply->param;

	QETH_CARD_TEXT(card, 4, "setaccb");
	if (cmd->hdr.return_code)
		return 0;
	qeth_setadpparms_inspect_rc(cmd);

	access_ctrl_req = &cmd->data.setadapterparms.data.set_access_ctrl;
	QETH_DBF_TEXT_(SETUP, 2, "setaccb");
	QETH_DBF_TEXT_(SETUP, 2, "%s", card->gdev->dev.kobj.name);
	QETH_DBF_TEXT_(SETUP, 2, "rc=%d",
		cmd->data.setadapterparms.hdr.return_code);
	if (cmd->data.setadapterparms.hdr.return_code !=
						SET_ACCESS_CTRL_RC_SUCCESS)
		QETH_DBF_MESSAGE(3, "ERR:SET_ACCESS_CTRL(%s,%d)==%d\n",
				card->gdev->dev.kobj.name,
				access_ctrl_req->subcmd_code,
				cmd->data.setadapterparms.hdr.return_code);
	switch (cmd->data.setadapterparms.hdr.return_code) {
	case SET_ACCESS_CTRL_RC_SUCCESS:
		if (card->options.isolation == ISOLATION_MODE_NONE) {
			dev_info(&card->gdev->dev,
			    "QDIO data connection isolation is deactivated\n");
		} else {
			dev_info(&card->gdev->dev,
			    "QDIO data connection isolation is activated\n");
		}
		break;
	case SET_ACCESS_CTRL_RC_ALREADY_NOT_ISOLATED:
		QETH_DBF_MESSAGE(2, "%s QDIO data connection isolation already "
				"deactivated\n", dev_name(&card->gdev->dev));
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_ALREADY_ISOLATED:
		QETH_DBF_MESSAGE(2, "%s QDIO data connection isolation already"
				" activated\n", dev_name(&card->gdev->dev));
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_NOT_SUPPORTED:
		dev_err(&card->gdev->dev, "Adapter does not "
			"support QDIO data connection isolation\n");
		break;
	case SET_ACCESS_CTRL_RC_NONE_SHARED_ADAPTER:
		dev_err(&card->gdev->dev,
			"Adapter is dedicated. "
			"QDIO data connection isolation not supported\n");
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_ACTIVE_CHECKSUM_OFF:
		dev_err(&card->gdev->dev,
			"TSO does not permit QDIO data connection isolation\n");
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_REFLREL_UNSUPPORTED:
		dev_err(&card->gdev->dev, "The adjacent switch port does not "
			"support reflective relay mode\n");
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_REFLREL_FAILED:
		dev_err(&card->gdev->dev, "The reflective relay mode cannot be "
					"enabled at the adjacent switch port");
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	case SET_ACCESS_CTRL_RC_REFLREL_DEACT_FAILED:
		dev_warn(&card->gdev->dev, "Turning off reflective relay mode "
					"at the adjacent switch failed\n");
		break;
	default:
		/* this should never happen */
		if (fallback)
			card->options.isolation = card->options.prev_isolation;
		break;
	}
	return 0;
}