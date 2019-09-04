#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct airo_info {int flags; int /*<<< orphan*/  sem; int /*<<< orphan*/  jobs; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  parm0; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  Resp ;
typedef  TYPE_1__ Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SETMODE ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  JOB_PROMISC ; 
 int /*<<< orphan*/  NOPROMISC ; 
 int /*<<< orphan*/  PROMISC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issuecommand (struct airo_info*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_set_promisc(struct airo_info *ai) {
	Cmd cmd;
	Resp rsp;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd=CMD_SETMODE;
	clear_bit(JOB_PROMISC, &ai->jobs);
	cmd.parm0=(ai->flags&IFF_PROMISC) ? PROMISC : NOPROMISC;
	issuecommand(ai, &cmd, &rsp);
	up(&ai->sem);
}