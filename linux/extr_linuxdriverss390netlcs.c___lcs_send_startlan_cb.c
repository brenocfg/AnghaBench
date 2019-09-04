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
struct lcs_cmd {TYPE_2__ cmd; } ;
struct lcs_card {int /*<<< orphan*/  portno; int /*<<< orphan*/  lan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
__lcs_send_startlan_cb(struct lcs_card *card, struct lcs_cmd *cmd)
{
	LCS_DBF_TEXT(2, trace, "srtlancb");
	card->lan_type = cmd->cmd.lcs_std_cmd.lan_type;
	card->portno = cmd->cmd.lcs_std_cmd.portno;
}