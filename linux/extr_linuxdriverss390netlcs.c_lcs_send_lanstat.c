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
struct TYPE_3__ {int /*<<< orphan*/  portno; int /*<<< orphan*/  lan_type; } ;
struct TYPE_4__ {TYPE_1__ lcs_std_cmd; } ;
struct lcs_cmd {TYPE_2__ cmd; int /*<<< orphan*/  initiator; int /*<<< orphan*/  cmd_code; } ;
struct lcs_card {int /*<<< orphan*/  portno; int /*<<< orphan*/  lan_type; } ;
struct lcs_buffer {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_CMD_LANSTAT ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_INITIATOR_TCPIP ; 
 int /*<<< orphan*/  LCS_STD_CMD_SIZE ; 
 int /*<<< orphan*/  __lcs_lanstat_cb ; 
 struct lcs_buffer* lcs_get_lancmd (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int lcs_send_lancmd (struct lcs_card*,struct lcs_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_send_lanstat(struct lcs_card *card)
{
	struct lcs_buffer *buffer;
	struct lcs_cmd *cmd;

	LCS_DBF_TEXT(2,trace, "cmdstat");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (struct lcs_cmd *) buffer->data;
	/* Setup lanstat command. */
	cmd->cmd_code = LCS_CMD_LANSTAT;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	cmd->cmd.lcs_std_cmd.lan_type = card->lan_type;
	cmd->cmd.lcs_std_cmd.portno = card->portno;
	return lcs_send_lancmd(card, buffer, __lcs_lanstat_cb);
}