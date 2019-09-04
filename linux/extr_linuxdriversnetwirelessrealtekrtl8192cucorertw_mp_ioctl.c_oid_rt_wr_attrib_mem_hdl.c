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
struct oid_par_priv {int dummy; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */

NDIS_STATUS oid_rt_wr_attrib_mem_hdl (struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);
	struct io_queue *pio_queue = (struct io_queue *)Adapter->pio_queue;
	struct intf_hdl	*pintfhdl = &pio_queue->intf;

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

#ifdef CONFIG_SDIO_HCI
	void (*_attrib_write)(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *pmem);
#endif

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

#ifdef CONFIG_SDIO_HCI
	_irqlevel_changed_(&oldirql, LOWER);
{
	u32 *plmem = (u32*)poid_par_priv->information_buf + 2;
	_attrib_write = pintfhdl->io_ops._attrib_write;
	_attrib_write(pintfhdl, *(u32*)poid_par_priv->information_buf,
				*((u32*)poid_par_priv->information_buf+1), (u8*)plmem);
}
	_irqlevel_changed_(&oldirql, RAISE);
#endif

_func_exit_;

	return status;
#else
	return 0;
#endif
}