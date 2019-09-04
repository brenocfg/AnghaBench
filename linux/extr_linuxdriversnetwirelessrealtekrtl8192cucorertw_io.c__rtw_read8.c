#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  (* _read8 ) (struct intf_hdl*,int /*<<< orphan*/ ) ;} ;
struct intf_hdl {TYPE_1__ io_ops; } ;
struct io_priv {struct intf_hdl intf; } ;
struct TYPE_5__ {struct io_priv iopriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

u8 _rtw_read8(_adapter *adapter, u32 addr)
{
	u8 r_val;
	//struct	io_queue  	*pio_queue = (struct io_queue *)adapter->pio_queue;
	struct io_priv *pio_priv = &adapter->iopriv;
	struct	intf_hdl		*pintfhdl = &(pio_priv->intf);
	u8 (*_read8)(struct intf_hdl *pintfhdl, u32 addr);
	_func_enter_;
	_read8 = pintfhdl->io_ops._read8;

	r_val = _read8(pintfhdl, addr);
	_func_exit_;
	return r_val;
}