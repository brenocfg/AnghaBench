#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  vnic_char; int /*<<< orphan*/  timeout; } ;
struct TYPE_10__ {int data_length; int sub_command; } ;
struct TYPE_9__ {int /*<<< orphan*/  vnic_char; } ;
struct TYPE_8__ {int /*<<< orphan*/  vnic_char; } ;
struct qeth_ipacmd_vnicc {TYPE_5__ getset_timeout; TYPE_4__ sub_hdr; TYPE_3__ set_char; TYPE_2__ query_cmds; } ;
struct TYPE_7__ {struct qeth_ipacmd_vnicc vnicc; } ;
struct qeth_ipa_cmd {TYPE_1__ data; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  channel; } ;
struct qeth_card {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  vnic_char; int /*<<< orphan*/  timeout; } ;
struct _qeth_l2_vnicc_request_cbctl {int sub_cmd; TYPE_6__ param; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_CMD_VNICC ; 
#define  IPA_VNICC_DISABLE 133 
#define  IPA_VNICC_ENABLE 132 
#define  IPA_VNICC_GET_TIMEOUT 131 
#define  IPA_VNICC_QUERY_CHARS 130 
#define  IPA_VNICC_QUERY_CMDS 129 
#define  IPA_VNICC_SET_TIMEOUT 128 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_l2_vnicc_makerc (struct qeth_card*,int) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_request_cb ; 
 int /*<<< orphan*/  qeth_release_buffer (int /*<<< orphan*/ ,struct qeth_cmd_buffer*) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int qeth_l2_vnicc_request(struct qeth_card *card,
				 struct _qeth_l2_vnicc_request_cbctl *cbctl)
{
	struct qeth_ipacmd_vnicc *req;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;
	int rc;

	QETH_CARD_TEXT(card, 2, "vniccreq");

	/* get new buffer for request */
	iob = qeth_get_ipacmd_buffer(card, IPA_CMD_VNICC, 0);
	if (!iob)
		return -ENOMEM;

	/* create header for request */
	cmd = __ipa_cmd(iob);
	req = &cmd->data.vnicc;

	/* create sub command header for request */
	req->sub_hdr.data_length = sizeof(req->sub_hdr);
	req->sub_hdr.sub_command = cbctl->sub_cmd;

	/* create sub command specific request fields */
	switch (cbctl->sub_cmd) {
	case IPA_VNICC_QUERY_CHARS:
		break;
	case IPA_VNICC_QUERY_CMDS:
		req->sub_hdr.data_length += sizeof(req->query_cmds);
		req->query_cmds.vnic_char = cbctl->param.vnic_char;
		break;
	case IPA_VNICC_ENABLE:
	case IPA_VNICC_DISABLE:
		req->sub_hdr.data_length += sizeof(req->set_char);
		req->set_char.vnic_char = cbctl->param.vnic_char;
		break;
	case IPA_VNICC_SET_TIMEOUT:
		req->getset_timeout.timeout = cbctl->param.timeout;
		/* fallthrough */
	case IPA_VNICC_GET_TIMEOUT:
		req->sub_hdr.data_length += sizeof(req->getset_timeout);
		req->getset_timeout.vnic_char = cbctl->param.vnic_char;
		break;
	default:
		qeth_release_buffer(iob->channel, iob);
		return -EOPNOTSUPP;
	}

	/* send request */
	rc = qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb,
			       (void *) cbctl);

	return qeth_l2_vnicc_makerc(card, rc);
}