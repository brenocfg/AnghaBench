#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int (* _write8 ) (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct intf_hdl {TYPE_1__ io_ops; } ;
struct io_priv {struct intf_hdl intf; } ;
struct adapter {struct io_priv iopriv; } ;

/* Variables and functions */
 int RTW_STATUS_CODE (int) ; 

int _rtw_write8(struct adapter *adapter, u32 addr, u8 val)
{
	/* struct	io_queue	*pio_queue = (struct io_queue *)adapter->pio_queue; */
	struct io_priv *pio_priv = &adapter->iopriv;
	struct	intf_hdl		*pintfhdl = &(pio_priv->intf);
	int (*_write8)(struct intf_hdl *pintfhdl, u32 addr, u8 val);
	int ret;

	_write8 = pintfhdl->io_ops._write8;

	ret = _write8(pintfhdl, addr, val);

	return RTW_STATUS_CODE(ret);
}