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
struct wilc_vif {TYPE_1__* hif_drv; } ;
struct TYPE_2__ {scalar_t__ hif_state; } ;

/* Variables and functions */
 scalar_t__ HOST_IF_CONNECTING ; 
 scalar_t__ HOST_IF_WAITING_CONN_RESP ; 
 int /*<<< orphan*/  wilc_disconnect (struct wilc_vif*,int) ; 

void wilc_resolve_disconnect_aberration(struct wilc_vif *vif)
{
	if (!vif->hif_drv)
		return;
	if (vif->hif_drv->hif_state == HOST_IF_WAITING_CONN_RESP ||
	    vif->hif_drv->hif_state == HOST_IF_CONNECTING)
		wilc_disconnect(vif, 1);
}