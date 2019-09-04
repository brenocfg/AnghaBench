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
struct _io_ops {int /*<<< orphan*/ * _write_port_cancel; int /*<<< orphan*/ * _read_port_cancel; int /*<<< orphan*/ * _write_port; int /*<<< orphan*/ * _write_mem; int /*<<< orphan*/ * _writeN; int /*<<< orphan*/ * _write32; int /*<<< orphan*/ * _write16; int /*<<< orphan*/ * _write8; int /*<<< orphan*/ * _read_port; int /*<<< orphan*/ * _read_mem; int /*<<< orphan*/ * _read32; int /*<<< orphan*/ * _read16; int /*<<< orphan*/ * _read8; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_read16 ; 
 int /*<<< orphan*/  usb_read32 ; 
 int /*<<< orphan*/  usb_read8 ; 
 int /*<<< orphan*/  usb_read_mem ; 
 int /*<<< orphan*/  usb_read_port ; 
 int /*<<< orphan*/  usb_read_port_cancel ; 
 int /*<<< orphan*/  usb_write16 ; 
 int /*<<< orphan*/  usb_write32 ; 
 int /*<<< orphan*/  usb_write8 ; 
 int /*<<< orphan*/  usb_writeN ; 
 int /*<<< orphan*/  usb_write_mem ; 
 int /*<<< orphan*/  usb_write_port ; 
 int /*<<< orphan*/  usb_write_port_cancel ; 

void rtl8192cu_set_intf_ops(struct _io_ops	*pops)
{
	_func_enter_;
	
	_rtw_memset((u8 *)pops, 0, sizeof(struct _io_ops));	

	pops->_read8 = &usb_read8;
	pops->_read16 = &usb_read16;
	pops->_read32 = &usb_read32;
	pops->_read_mem = &usb_read_mem;
	pops->_read_port = &usb_read_port;	
	
	pops->_write8 = &usb_write8;
	pops->_write16 = &usb_write16;
	pops->_write32 = &usb_write32;
	pops->_writeN = &usb_writeN;
	
#ifdef CONFIG_USB_SUPPORT_ASYNC_VDN_REQ	
	pops->_write8_async= &usb_async_write8;
	pops->_write16_async = &usb_async_write16;
	pops->_write32_async = &usb_async_write32;
#endif	
	pops->_write_mem = &usb_write_mem;
	pops->_write_port = &usb_write_port;

	pops->_read_port_cancel = &usb_read_port_cancel;
	pops->_write_port_cancel = &usb_write_port_cancel;

#ifdef CONFIG_USB_INTERRUPT_IN_PIPE
	pops->_read_interrupt = &usb_read_interrupt;
#endif

	_func_exit_;

}