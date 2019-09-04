#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {TYPE_1__* frame_reg; scalar_t__ monitor_flag; } ;
struct wilc {int vif_num; TYPE_2__** vif; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndev; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ reg; } ;

/* Variables and functions */
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wfi_monitor_rx (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wfi_p2p_rx (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

void wilc_wfi_mgmt_rx(struct wilc *wilc, u8 *buff, u32 size)
{
	int i = 0;
	struct wilc_vif *vif;

	for (i = 0; i < wilc->vif_num; i++) {
		vif = netdev_priv(wilc->vif[i]->ndev);
		if (vif->monitor_flag) {
			wilc_wfi_monitor_rx(buff, size);
			return;
		}
	}

	vif = netdev_priv(wilc->vif[1]->ndev);
	if ((buff[0] == vif->frame_reg[0].type && vif->frame_reg[0].reg) ||
	    (buff[0] == vif->frame_reg[1].type && vif->frame_reg[1].reg))
		wilc_wfi_p2p_rx(wilc->vif[1]->ndev, buff, size);
}