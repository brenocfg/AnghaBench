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
struct platform_device {int dummy; } ;

/* Variables and functions */
 unsigned int* IFX_PP32_ENET_MAC_CFG ; 
 int* IFX_PP32_ETOP_CFG ; 
 unsigned int* IFX_PP32_ETOP_IG_PLEN_CTRL ; 
 unsigned int* IFX_PP32_ETOP_MDIO_CFG ; 
 int /*<<< orphan*/  IFX_RCU_DOMAIN_PPE ; 
 int /*<<< orphan*/  IFX_RCU_MODULE_PTM ; 
 int /*<<< orphan*/  ifx_rcu_rst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reset_ppe(struct platform_device *pdev)
{
#ifdef MODULE
    unsigned int etop_cfg;
    unsigned int etop_mdio_cfg;
    unsigned int etop_ig_plen_ctrl;
    unsigned int enet_mac_cfg;

    etop_cfg            = *IFX_PP32_ETOP_CFG;
    etop_mdio_cfg       = *IFX_PP32_ETOP_MDIO_CFG;
    etop_ig_plen_ctrl   = *IFX_PP32_ETOP_IG_PLEN_CTRL;
    enet_mac_cfg        = *IFX_PP32_ENET_MAC_CFG;

    *IFX_PP32_ETOP_CFG  = (*IFX_PP32_ETOP_CFG & ~0x03C0) | 0x0001;

    //  reset PPE
    ifx_rcu_rst(IFX_RCU_DOMAIN_PPE, IFX_RCU_MODULE_PTM);

    *IFX_PP32_ETOP_MDIO_CFG     = etop_mdio_cfg;
    *IFX_PP32_ETOP_IG_PLEN_CTRL = etop_ig_plen_ctrl;
    *IFX_PP32_ENET_MAC_CFG      = enet_mac_cfg;
    *IFX_PP32_ETOP_CFG          = etop_cfg;
#endif
}