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
struct rtl_ops {int /*<<< orphan*/  autosuspend_en; int /*<<< orphan*/  hw_phy_cfg; void* in_nway; int /*<<< orphan*/  eee_set; void* eee_get; int /*<<< orphan*/  unload; int /*<<< orphan*/  down; int /*<<< orphan*/  up; int /*<<< orphan*/  disable; void* enable; int /*<<< orphan*/  init; } ;
struct r8152 {int version; int /*<<< orphan*/  netdev; struct rtl_ops rtl_ops; } ;

/* Variables and functions */
 int ENODEV ; 
#define  RTL_VER_01 136 
#define  RTL_VER_02 135 
#define  RTL_VER_03 134 
#define  RTL_VER_04 133 
#define  RTL_VER_05 132 
#define  RTL_VER_06 131 
#define  RTL_VER_07 130 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 int /*<<< orphan*/  netif_err (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 void* r8152_get_eee ; 
 int /*<<< orphan*/  r8152_set_eee ; 
 int /*<<< orphan*/  r8152b_hw_phy_cfg ; 
 int /*<<< orphan*/  r8152b_init ; 
 void* r8153_get_eee ; 
 int /*<<< orphan*/  r8153_hw_phy_cfg ; 
 int /*<<< orphan*/  r8153_init ; 
 int /*<<< orphan*/  r8153_set_eee ; 
 int /*<<< orphan*/  r8153b_hw_phy_cfg ; 
 int /*<<< orphan*/  r8153b_init ; 
 int /*<<< orphan*/  r8153b_set_eee ; 
 int /*<<< orphan*/  rtl8152_disable ; 
 int /*<<< orphan*/  rtl8152_down ; 
 void* rtl8152_enable ; 
 void* rtl8152_in_nway ; 
 int /*<<< orphan*/  rtl8152_unload ; 
 int /*<<< orphan*/  rtl8152_up ; 
 int /*<<< orphan*/  rtl8153_disable ; 
 int /*<<< orphan*/  rtl8153_down ; 
 void* rtl8153_enable ; 
 void* rtl8153_in_nway ; 
 int /*<<< orphan*/  rtl8153_runtime_enable ; 
 int /*<<< orphan*/  rtl8153_unload ; 
 int /*<<< orphan*/  rtl8153_up ; 
 int /*<<< orphan*/  rtl8153b_disable ; 
 int /*<<< orphan*/  rtl8153b_down ; 
 int /*<<< orphan*/  rtl8153b_runtime_enable ; 
 int /*<<< orphan*/  rtl8153b_unload ; 
 int /*<<< orphan*/  rtl8153b_up ; 
 int /*<<< orphan*/  rtl_runtime_suspend_enable ; 

__attribute__((used)) static int rtl_ops_init(struct r8152 *tp)
{
	struct rtl_ops *ops = &tp->rtl_ops;
	int ret = 0;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		ops->init		= r8152b_init;
		ops->enable		= rtl8152_enable;
		ops->disable		= rtl8152_disable;
		ops->up			= rtl8152_up;
		ops->down		= rtl8152_down;
		ops->unload		= rtl8152_unload;
		ops->eee_get		= r8152_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8152_in_nway;
		ops->hw_phy_cfg		= r8152b_hw_phy_cfg;
		ops->autosuspend_en	= rtl_runtime_suspend_enable;
		break;

	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ops->init		= r8153_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153_up;
		ops->down		= rtl8153_down;
		ops->unload		= rtl8153_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8153_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153_hw_phy_cfg;
		ops->autosuspend_en	= rtl8153_runtime_enable;
		break;

	case RTL_VER_08:
	case RTL_VER_09:
		ops->init		= r8153b_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153b_disable;
		ops->up			= rtl8153b_up;
		ops->down		= rtl8153b_down;
		ops->unload		= rtl8153b_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8153b_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153b_hw_phy_cfg;
		ops->autosuspend_en	= rtl8153b_runtime_enable;
		break;

	default:
		ret = -ENODEV;
		netif_err(tp, probe, tp->netdev, "Unknown Device\n");
		break;
	}

	return ret;
}