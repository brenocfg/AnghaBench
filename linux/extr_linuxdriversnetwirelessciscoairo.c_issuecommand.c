#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct airo_info {TYPE_1__* dev; } ;
struct TYPE_8__ {int parm0; int parm1; int parm2; int cmd; } ;
struct TYPE_7__ {int status; int rsp0; int rsp1; int rsp2; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Resp ;
typedef  TYPE_3__ Cmd ;

/* Variables and functions */
 int CMD_SOFTRESET ; 
 int /*<<< orphan*/  COMMAND ; 
 int COMMAND_BUSY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EVSTAT ; 
 int EV_CLEARCOMMANDBUSY ; 
 int EV_CMD ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PARAM0 ; 
 int /*<<< orphan*/  PARAM1 ; 
 int /*<<< orphan*/  PARAM2 ; 
 int /*<<< orphan*/  RESP0 ; 
 int /*<<< orphan*/  RESP1 ; 
 int /*<<< orphan*/  RESP2 ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  in_atomic () ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static u16 issuecommand(struct airo_info *ai, Cmd *pCmd, Resp *pRsp) {
        // Im really paranoid about letting it run forever!
	int max_tries = 600000;

	if (IN4500(ai, EVSTAT) & EV_CMD)
		OUT4500(ai, EVACK, EV_CMD);

	OUT4500(ai, PARAM0, pCmd->parm0);
	OUT4500(ai, PARAM1, pCmd->parm1);
	OUT4500(ai, PARAM2, pCmd->parm2);
	OUT4500(ai, COMMAND, pCmd->cmd);

	while (max_tries-- && (IN4500(ai, EVSTAT) & EV_CMD) == 0) {
		if ((IN4500(ai, COMMAND)) == pCmd->cmd)
			// PC4500 didn't notice command, try again
			OUT4500(ai, COMMAND, pCmd->cmd);
		if (!in_atomic() && (max_tries & 255) == 0)
			schedule();
	}

	if ( max_tries == -1 ) {
		airo_print_err(ai->dev->name,
			"Max tries exceeded when issuing command");
		if (IN4500(ai, COMMAND) & COMMAND_BUSY)
			OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
		return ERROR;
	}

	// command completed
	pRsp->status = IN4500(ai, STATUS);
	pRsp->rsp0 = IN4500(ai, RESP0);
	pRsp->rsp1 = IN4500(ai, RESP1);
	pRsp->rsp2 = IN4500(ai, RESP2);
	if ((pRsp->status & 0xff00)!=0 && pCmd->cmd != CMD_SOFTRESET)
		airo_print_err(ai->dev->name,
			"cmd:%x status:%x rsp0:%x rsp1:%x rsp2:%x",
			pCmd->cmd, pRsp->status, pRsp->rsp0, pRsp->rsp1,
			pRsp->rsp2);

	// clear stuck command busy if necessary
	if (IN4500(ai, COMMAND) & COMMAND_BUSY) {
		OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
	}
	// acknowledge processing the status/response
	OUT4500(ai, EVACK, EV_CMD);

	return SUCCESS;
}