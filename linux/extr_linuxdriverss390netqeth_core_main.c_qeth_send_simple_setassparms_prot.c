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
typedef  int /*<<< orphan*/  u16 ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ipa_funcs { ____Placeholder_qeth_ipa_funcs } qeth_ipa_funcs ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 struct qeth_cmd_buffer* qeth_get_setassparms_cmd (struct qeth_card*,int,int /*<<< orphan*/ ,int,int) ; 
 int qeth_send_setassparms (struct qeth_card*,struct qeth_cmd_buffer*,int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_setassparms_cb ; 

int qeth_send_simple_setassparms_prot(struct qeth_card *card,
				      enum qeth_ipa_funcs ipa_func,
				      u16 cmd_code, long data,
				      enum qeth_prot_versions prot)
{
	int rc;
	int length = 0;
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT_(card, 4, "simassp%i", prot);
	if (data)
		length = sizeof(__u32);
	iob = qeth_get_setassparms_cmd(card, ipa_func, cmd_code, length, prot);
	if (!iob)
		return -ENOMEM;
	rc = qeth_send_setassparms(card, iob, length, data,
				   qeth_setassparms_cb, NULL);
	return rc;
}