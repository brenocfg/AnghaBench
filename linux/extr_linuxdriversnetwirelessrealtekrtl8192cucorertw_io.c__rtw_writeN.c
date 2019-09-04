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
struct io_priv {int /*<<< orphan*/  intf; } ;
struct TYPE_4__ {int (* _writeN ) (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct intf_hdl {TYPE_1__ io_ops; } ;
struct TYPE_5__ {struct io_priv iopriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int RTW_STATUS_CODE (int) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

int _rtw_writeN(_adapter *adapter, u32 addr ,u32 length , u8 *pdata)
{
	//struct	io_queue  	*pio_queue = (struct io_queue *)adapter->pio_queue;
	struct io_priv *pio_priv = &adapter->iopriv;
        struct	intf_hdl	*pintfhdl = (struct intf_hdl*)(&(pio_priv->intf));
	int (*_writeN)(struct intf_hdl *pintfhdl, u32 addr,u32 length, u8 *pdata);
	int ret;
	_func_enter_;
	_writeN = pintfhdl->io_ops._writeN;

	ret = _writeN(pintfhdl, addr,length,pdata);
	_func_exit_;

	return RTW_STATUS_CODE(ret);
}