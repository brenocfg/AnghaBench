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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ POLLING_LLT_THRESHOLD ; 
 int /*<<< orphan*/  REG_LLT_INIT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 int _LLT_INIT_ADDR (int) ; 
 int _LLT_INIT_DATA (int) ; 
 scalar_t__ _LLT_NO_ACTIVE ; 
 int _LLT_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ _LLT_OP_VALUE (int) ; 
 int /*<<< orphan*/  _LLT_WRITE_ACCESS ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 _LLTWrite(struct adapter *padapter, u32 address, u32 data)
{
	s32	status = _SUCCESS;
	s32	count = 0;
	u32	value = _LLT_INIT_ADDR(address) | _LLT_INIT_DATA(data) | _LLT_OP(_LLT_WRITE_ACCESS);
	u16	LLTReg = REG_LLT_INIT;

	usb_write32(padapter, LLTReg, value);

	/* polling */
	do {
		value = usb_read32(padapter, LLTReg);
		if (_LLT_NO_ACTIVE == _LLT_OP_VALUE(value))
			break;

		if (count > POLLING_LLT_THRESHOLD) {
			RT_TRACE(_module_hal_init_c_, _drv_err_, ("Failed to polling write LLT done at address %d!\n", address));
			status = _FAIL;
			break;
		}
		udelay(5);
	} while (count++);

	return status;
}