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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_checksum_cmd {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ipa_funcs { ____Placeholder_qeth_ipa_funcs } qeth_ipa_funcs ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct qeth_cmd_buffer* qeth_get_setassparms_cmd (struct qeth_card*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qeth_ipa_checksum_run_cmd_cb ; 
 int qeth_send_setassparms (struct qeth_card*,struct qeth_cmd_buffer*,int,long,int /*<<< orphan*/ ,struct qeth_checksum_cmd*) ; 

__attribute__((used)) static int qeth_ipa_checksum_run_cmd(struct qeth_card *card,
				     enum qeth_ipa_funcs ipa_func,
				     __u16 cmd_code, long data,
				     struct qeth_checksum_cmd *chksum_cb,
				     enum qeth_prot_versions prot)
{
	struct qeth_cmd_buffer *iob;
	int rc = -ENOMEM;

	QETH_CARD_TEXT(card, 4, "chkdocmd");
	iob = qeth_get_setassparms_cmd(card, ipa_func, cmd_code,
				       sizeof(__u32), prot);
	if (iob)
		rc = qeth_send_setassparms(card, iob, sizeof(__u32), data,
					   qeth_ipa_checksum_run_cmd_cb,
					   chksum_cb);
	return rc;
}