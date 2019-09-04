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
struct cmd_msg_parm {int /*<<< orphan*/ * buf; int /*<<< orphan*/  sz; int /*<<< orphan*/  eid; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  rtl8192c_FillH2CCmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u8 rtl8192c_h2c_msg_hdl(_adapter *padapter, unsigned char *pbuf)
{	
	u8 ElementID, CmdLen;
	u8 *pCmdBuffer;
	struct cmd_msg_parm  *pcmdmsg;
	
	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	pcmdmsg = (struct cmd_msg_parm*)pbuf;
	ElementID = pcmdmsg->eid;
	CmdLen = pcmdmsg->sz;
	pCmdBuffer = pcmdmsg->buf;

	rtl8192c_FillH2CCmd(padapter, ElementID, CmdLen, pCmdBuffer);

	return H2C_SUCCESS;
}