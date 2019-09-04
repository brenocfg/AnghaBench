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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct intf_hdl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  usbctrl_vendorreq (struct intf_hdl*,int,int,int,int*,int,int) ; 

__attribute__((used)) static u32 usb_read32(struct intf_hdl *pintfhdl, u32 addr)
{
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	u32 data=0;
	
	_func_enter_;

	request = 0x05;
	requesttype = 0x01;//read_in
	index = 0;//n/a

	wvalue = (u16)(addr&0x0000ffff);
	len = 4;	
	
	usbctrl_vendorreq(pintfhdl, request, wvalue, index, &data, len, requesttype);

	_func_exit_;

	return le32_to_cpu(data);
	
}