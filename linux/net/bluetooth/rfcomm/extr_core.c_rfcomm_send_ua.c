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
typedef  int /*<<< orphan*/  u8 ;
struct rfcomm_session {int /*<<< orphan*/  initiator; } ;
struct rfcomm_cmd {int /*<<< orphan*/  fcs; int /*<<< orphan*/  len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_UA ; 
 int /*<<< orphan*/  __addr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __fcs2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __len8 (int /*<<< orphan*/ ) ; 
 int rfcomm_send_cmd (struct rfcomm_session*,struct rfcomm_cmd*) ; 

__attribute__((used)) static int rfcomm_send_ua(struct rfcomm_session *s, u8 dlci)
{
	struct rfcomm_cmd cmd;

	BT_DBG("%p dlci %d", s, dlci);

	cmd.addr = __addr(!s->initiator, dlci);
	cmd.ctrl = __ctrl(RFCOMM_UA, 1);
	cmd.len  = __len8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	return rfcomm_send_cmd(s, &cmd);
}