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
struct sdio_func {int dummy; } ;
struct TYPE_2__ {scalar_t__ sys_sdio_irq_thd; } ;
struct dvobj_priv {TYPE_1__ intf_data; } ;
typedef  TYPE_1__* PSDIO_DATA ;

/* Variables and functions */
 scalar_t__ current ; 
 struct dvobj_priv* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static bool rtw_sdio_claim_host_needed(struct sdio_func *func)
{
	struct dvobj_priv *dvobj = sdio_get_drvdata(func);
	PSDIO_DATA sdio_data = &dvobj->intf_data;

	if (sdio_data->sys_sdio_irq_thd && sdio_data->sys_sdio_irq_thd == current)
		return false;
	return true;
}