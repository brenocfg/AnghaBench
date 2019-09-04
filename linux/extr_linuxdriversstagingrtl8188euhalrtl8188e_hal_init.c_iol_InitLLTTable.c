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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INIT_LLT ; 
 scalar_t__ REG_TDECTRL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  iol_execute (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iol_mode_enable (struct adapter*,int) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 iol_InitLLTTable(struct adapter *padapter, u8 txpktbuf_bndy)
{
	s32 rst = _SUCCESS;

	iol_mode_enable(padapter, 1);
	usb_write8(padapter, REG_TDECTRL+1, txpktbuf_bndy);
	rst = iol_execute(padapter, CMD_INIT_LLT);
	iol_mode_enable(padapter, 0);
	return rst;
}