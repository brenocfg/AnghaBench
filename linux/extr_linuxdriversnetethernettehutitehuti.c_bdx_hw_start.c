#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int pktsz; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct bdx_priv {int rdintcm; int tdintcm; TYPE_4__* nic; TYPE_3__* pdev; struct net_device* ndev; TYPE_2__ rxf_fifo0; } ;
struct TYPE_8__ {scalar_t__ irq_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  ENTER ; 
 int GMAC_RX_FILTER_AB ; 
 int GMAC_RX_FILTER_AM ; 
 int GMAC_RX_FILTER_OSEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IRQ_MSI ; 
 int MAX_FRAME_AB_VAL ; 
 int /*<<< orphan*/  RET (int) ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bdx_enable_interrupts (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_isr_napi ; 
 int /*<<< orphan*/  bdx_link_changed (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_restore_mac (struct net_device*,struct bdx_priv*) ; 
 int /*<<< orphan*/  regCTRLST ; 
 int regCTRLST_BASE ; 
 int regCTRLST_RX_ENA ; 
 int regCTRLST_TX_ENA ; 
 int /*<<< orphan*/  regFRM_LENGTH ; 
 int /*<<< orphan*/  regGMAC_RXF_A ; 
 int /*<<< orphan*/  regMAX_FRAME_A ; 
 int /*<<< orphan*/  regPAUSE_QUANT ; 
 int /*<<< orphan*/  regRDINTCM0 ; 
 int /*<<< orphan*/  regRDINTCM2 ; 
 int /*<<< orphan*/  regRX_FIFO_SECTION ; 
 int /*<<< orphan*/  regRX_FULLNESS ; 
 int /*<<< orphan*/  regTDINTCM0 ; 
 int /*<<< orphan*/  regTX_FIFO_SECTION ; 
 int /*<<< orphan*/  regTX_FULLNESS ; 
 int /*<<< orphan*/  regVGLB ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int bdx_hw_start(struct bdx_priv *priv)
{
	int rc = -EIO;
	struct net_device *ndev = priv->ndev;

	ENTER;
	bdx_link_changed(priv);

	/* 10G overall max length (vlan, eth&ip header, ip payload, crc) */
	WRITE_REG(priv, regFRM_LENGTH, 0X3FE0);
	WRITE_REG(priv, regPAUSE_QUANT, 0x96);
	WRITE_REG(priv, regRX_FIFO_SECTION, 0x800010);
	WRITE_REG(priv, regTX_FIFO_SECTION, 0xE00010);
	WRITE_REG(priv, regRX_FULLNESS, 0);
	WRITE_REG(priv, regTX_FULLNESS, 0);
	WRITE_REG(priv, regCTRLST,
		  regCTRLST_BASE | regCTRLST_RX_ENA | regCTRLST_TX_ENA);

	WRITE_REG(priv, regVGLB, 0);
	WRITE_REG(priv, regMAX_FRAME_A,
		  priv->rxf_fifo0.m.pktsz & MAX_FRAME_AB_VAL);

	DBG("RDINTCM=%08x\n", priv->rdintcm);	/*NOTE: test script uses this */
	WRITE_REG(priv, regRDINTCM0, priv->rdintcm);
	WRITE_REG(priv, regRDINTCM2, 0);	/*cpu_to_le32(rcm.val)); */

	DBG("TDINTCM=%08x\n", priv->tdintcm);	/*NOTE: test script uses this */
	WRITE_REG(priv, regTDINTCM0, priv->tdintcm);	/* old val = 0x300064 */

	/* Enable timer interrupt once in 2 secs. */
	/*WRITE_REG(priv, regGTMR0, ((GTMR_SEC * 2) & GTMR_DATA)); */
	bdx_restore_mac(priv->ndev, priv);

	WRITE_REG(priv, regGMAC_RXF_A, GMAC_RX_FILTER_OSEN |
		  GMAC_RX_FILTER_AM | GMAC_RX_FILTER_AB);

#define BDX_IRQ_TYPE	((priv->nic->irq_type == IRQ_MSI) ? 0 : IRQF_SHARED)

	rc = request_irq(priv->pdev->irq, bdx_isr_napi, BDX_IRQ_TYPE,
			 ndev->name, ndev);
	if (rc)
		goto err_irq;
	bdx_enable_interrupts(priv);

	RET(0);

err_irq:
	RET(rc);
}