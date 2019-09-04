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
struct TYPE_2__ {void* sys_sdio_irq_thd; } ;
struct dvobj_priv {TYPE_1__ intf_data; } ;
typedef  TYPE_1__* PSDIO_DATA ;

/* Variables and functions */

inline void rtw_sdio_set_irq_thd(struct dvobj_priv *dvobj, void *thd_hdl)
{
	PSDIO_DATA sdio_data = &dvobj->intf_data;

	sdio_data->sys_sdio_irq_thd = thd_hdl;
}