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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {TYPE_1__* gdev; int /*<<< orphan*/  write; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ipa_cmds { ____Placeholder_qeth_ipa_cmds } qeth_ipa_cmds ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ipa_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qeth_fill_ipacmd_header (struct qeth_card*,int /*<<< orphan*/ ,int,int) ; 
 struct qeth_cmd_buffer* qeth_get_buffer (int /*<<< orphan*/ *) ; 

struct qeth_cmd_buffer *qeth_get_ipacmd_buffer(struct qeth_card *card,
		enum qeth_ipa_cmds ipacmd, enum qeth_prot_versions prot)
{
	struct qeth_cmd_buffer *iob;

	iob = qeth_get_buffer(&card->write);
	if (iob) {
		qeth_fill_ipacmd_header(card, __ipa_cmd(iob), ipacmd, prot);
	} else {
		dev_warn(&card->gdev->dev,
			 "The qeth driver ran out of channel command buffers\n");
		QETH_DBF_MESSAGE(1, "%s The qeth driver ran out of channel command buffers",
				 dev_name(&card->gdev->dev));
	}

	return iob;
}