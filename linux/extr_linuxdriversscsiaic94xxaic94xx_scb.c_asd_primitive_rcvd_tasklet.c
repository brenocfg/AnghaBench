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
typedef  int u8 ;
typedef  int u32 ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;struct asd_sas_phy** sas_phy; } ;
struct done_list_struct {int* status_block; } ;
struct asd_sas_phy {int /*<<< orphan*/  sas_prim_lock; int /*<<< orphan*/  sas_prim; } ;
struct asd_phy {int dummy; } ;
struct asd_ha_struct {struct asd_phy* phys; struct sas_ha_struct sas_ha; } ;
struct asd_ascb {struct asd_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,...) ; 
#define  LmBROADCH 135 
#define  LmBROADRVCH0 134 
#define  LmBROADRVCH1 133 
#define  LmBROADSES 132 
#define  LmHARDRST 131 
#define  LmPRMSTAT0BYTE0 130 
#define  LmPRMSTAT1BYTE0 129 
#define  LmUNKNOWNP 128 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 int /*<<< orphan*/  PORTE_HARD_RESET ; 
 int /*<<< orphan*/  asd_deform_port (struct asd_ha_struct*,struct asd_phy*) ; 
 int /*<<< orphan*/  ffs (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_primitive_rcvd_tasklet(struct asd_ascb *ascb,
				       struct done_list_struct *dl,
				       int phy_id)
{
	unsigned long flags;
	struct sas_ha_struct *sas_ha = &ascb->ha->sas_ha;
	struct asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	struct asd_ha_struct *asd_ha = ascb->ha;
	struct asd_phy *phy = &asd_ha->phys[phy_id];
	u8  reg  = dl->status_block[1];
	u32 cont = dl->status_block[2] << ((reg & 3)*8);

	reg &= ~3;
	switch (reg) {
	case LmPRMSTAT0BYTE0:
		switch (cont) {
		case LmBROADCH:
		case LmBROADRVCH0:
		case LmBROADRVCH1:
		case LmBROADSES:
			ASD_DPRINTK("phy%d: BROADCAST change received:%d\n",
				    phy_id, cont);
			spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
			sas_phy->sas_prim = ffs(cont);
			spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
			sas_ha->notify_port_event(sas_phy,PORTE_BROADCAST_RCVD);
			break;

		case LmUNKNOWNP:
			ASD_DPRINTK("phy%d: unknown BREAK\n", phy_id);
			break;

		default:
			ASD_DPRINTK("phy%d: primitive reg:0x%x, cont:0x%04x\n",
				    phy_id, reg, cont);
			break;
		}
		break;
	case LmPRMSTAT1BYTE0:
		switch (cont) {
		case LmHARDRST:
			ASD_DPRINTK("phy%d: HARD_RESET primitive rcvd\n",
				    phy_id);
			/* The sequencer disables all phys on that port.
			 * We have to re-enable the phys ourselves. */
			asd_deform_port(asd_ha, phy);
			sas_ha->notify_port_event(sas_phy, PORTE_HARD_RESET);
			break;

		default:
			ASD_DPRINTK("phy%d: primitive reg:0x%x, cont:0x%04x\n",
				    phy_id, reg, cont);
			break;
		}
		break;
	default:
		ASD_DPRINTK("unknown primitive register:0x%x\n",
			    dl->status_block[1]);
		break;
	}
}