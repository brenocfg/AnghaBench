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
typedef  int /*<<< orphan*/  FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MSGACCEPTED ; 
 int /*<<< orphan*/  CMD_TRANSFERINFO ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  REG_INST ; 
 unsigned int STAT_BUSMASK ; 
 unsigned int STAT_INT ; 
 unsigned int STAT_MESGIN ; 
 unsigned int STAT_PARITYERROR ; 
 int /*<<< orphan*/  fas216_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int fas216_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int fas216_wait_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fas216_get_msg_byte(FAS216_Info *info)
{
	unsigned int stat = fas216_wait_cmd(info, CMD_MSGACCEPTED);

	if ((stat & STAT_INT) == 0)
		goto timedout;

	if ((stat & STAT_BUSMASK) != STAT_MESGIN)
		goto unexpected_phase_change;

	fas216_readb(info, REG_INST);

	stat = fas216_wait_cmd(info, CMD_TRANSFERINFO);

	if ((stat & STAT_INT) == 0)
		goto timedout;

	if (stat & STAT_PARITYERROR)
		goto parity_error;

	if ((stat & STAT_BUSMASK) != STAT_MESGIN)
		goto unexpected_phase_change;

	fas216_readb(info, REG_INST);

	return fas216_readb(info, REG_FF);

timedout:
	fas216_log(info, LOG_ERROR, "timed out waiting for message byte");
	return -1;

unexpected_phase_change:
	fas216_log(info, LOG_ERROR, "unexpected phase change: status = %02x", stat);
	return -2;

parity_error:
	fas216_log(info, LOG_ERROR, "parity error during message in phase");
	return -3;
}