#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _i16 ;
typedef  int /*<<< orphan*/  _SlOpcode_t ;
struct TYPE_9__ {int RxDescLen; scalar_t__ TxDescLen; int /*<<< orphan*/  Opcode; } ;
typedef  TYPE_3__ _SlCmdCtrl_t ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_2__ Rsp; TYPE_1__ member_0; } ;
typedef  TYPE_4__ _SlBasicCmdMsg_u ;
typedef  int /*<<< orphan*/  _BasicResponse_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_RET_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SlDrvCmdOp (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

_i16 _SlDrvBasicCmd(_SlOpcode_t Opcode)
{
    _SlBasicCmdMsg_u       Msg = {{0, 0}};
    _SlCmdCtrl_t           CmdCtrl;

    CmdCtrl.Opcode = Opcode;
    CmdCtrl.TxDescLen = 0;
    CmdCtrl.RxDescLen = sizeof(_BasicResponse_t);


    VERIFY_RET_OK(_SlDrvCmdOp((_SlCmdCtrl_t *)&CmdCtrl, &Msg, NULL));

    return (_i16)Msg.Rsp.status;
}