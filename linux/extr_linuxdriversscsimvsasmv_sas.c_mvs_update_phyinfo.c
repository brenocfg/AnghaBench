#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sas_identify_frame {int dummy; } ;
struct TYPE_4__ {int device_type; int /*<<< orphan*/  target_port_protocols; } ;
struct asd_sas_phy {int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  oob_mode; } ;
struct mvs_phy {int phy_type; int phy_attached; int att_dev_sas_addr; int frame_rcvd_size; int att_dev_info; int /*<<< orphan*/  irq_status; TYPE_1__ identify; struct asd_sas_phy sas_phy; scalar_t__ phy_status; scalar_t__ frame_rcvd; } ;
struct mvs_info {int id; TYPE_2__* chip; int /*<<< orphan*/  dev; struct mvs_phy* phy; } ;
struct dev_to_host_fis {int dummy; } ;
struct TYPE_6__ {int (* oob_done ) (struct mvs_info*,int) ;int (* read_port_irq_mask ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* write_port_irq_stat ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_work_around ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* write_port_irq_mask ) (struct mvs_info*,int,int) ;int /*<<< orphan*/  (* fix_phy_info ) (struct mvs_info*,int,struct sas_identify_frame*) ;int /*<<< orphan*/  (* read_port_irq_stat ) (struct mvs_info*,int) ;} ;
struct TYPE_5__ {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 TYPE_3__* MVS_CHIP_DISP ; 
 int PHYEV_SIG_FIS ; 
 int PORT_DEV_TYPE_MASK ; 
 int PORT_SSP_INIT_MASK ; 
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_OOB_MODE ; 
 int SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  SAS_PROTOCOL_SMP ; 
 int /*<<< orphan*/  SAS_PROTOCOL_SSP ; 
 int /*<<< orphan*/  SAS_PROTOCOL_STP ; 
 int /*<<< orphan*/  SATA_OOB_MODE ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_dprintk (char*,int,int) ; 
 int /*<<< orphan*/  mvs_get_d2h_reg (struct mvs_info*,int,struct sas_identify_frame*) ; 
 scalar_t__ mvs_is_phy_ready (struct mvs_info*,int) ; 
 scalar_t__ mvs_is_sig_fis_received (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_sig_remove_timer (struct mvs_phy*) ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,int) ; 
 int stub2 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub3 (struct mvs_info*,int,struct sas_identify_frame*) ; 
 int stub4 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub5 (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub7 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 

void mvs_update_phyinfo(struct mvs_info *mvi, int i, int get_st)
{
	struct mvs_phy *phy = &mvi->phy[i];
	struct sas_identify_frame *id;

	id = (struct sas_identify_frame *)phy->frame_rcvd;

	if (get_st) {
		phy->irq_status = MVS_CHIP_DISP->read_port_irq_stat(mvi, i);
		phy->phy_status = mvs_is_phy_ready(mvi, i);
	}

	if (phy->phy_status) {
		int oob_done = 0;
		struct asd_sas_phy *sas_phy = &mvi->phy[i].sas_phy;

		oob_done = MVS_CHIP_DISP->oob_done(mvi, i);

		MVS_CHIP_DISP->fix_phy_info(mvi, i, id);
		if (phy->phy_type & PORT_TYPE_SATA) {
			phy->identify.target_port_protocols = SAS_PROTOCOL_STP;
			if (mvs_is_sig_fis_received(phy->irq_status)) {
				mvs_sig_remove_timer(phy);
				phy->phy_attached = 1;
				phy->att_dev_sas_addr =
					i + mvi->id * mvi->chip->n_phy;
				if (oob_done)
					sas_phy->oob_mode = SATA_OOB_MODE;
				phy->frame_rcvd_size =
				    sizeof(struct dev_to_host_fis);
				mvs_get_d2h_reg(mvi, i, id);
			} else {
				u32 tmp;
				dev_printk(KERN_DEBUG, mvi->dev,
					"Phy%d : No sig fis\n", i);
				tmp = MVS_CHIP_DISP->read_port_irq_mask(mvi, i);
				MVS_CHIP_DISP->write_port_irq_mask(mvi, i,
						tmp | PHYEV_SIG_FIS);
				phy->phy_attached = 0;
				phy->phy_type &= ~PORT_TYPE_SATA;
				goto out_done;
			}
		}	else if (phy->phy_type & PORT_TYPE_SAS
			|| phy->att_dev_info & PORT_SSP_INIT_MASK) {
			phy->phy_attached = 1;
			phy->identify.device_type =
				phy->att_dev_info & PORT_DEV_TYPE_MASK;

			if (phy->identify.device_type == SAS_END_DEVICE)
				phy->identify.target_port_protocols =
							SAS_PROTOCOL_SSP;
			else if (phy->identify.device_type != SAS_PHY_UNUSED)
				phy->identify.target_port_protocols =
							SAS_PROTOCOL_SMP;
			if (oob_done)
				sas_phy->oob_mode = SAS_OOB_MODE;
			phy->frame_rcvd_size =
			    sizeof(struct sas_identify_frame);
		}
		memcpy(sas_phy->attached_sas_addr,
			&phy->att_dev_sas_addr, SAS_ADDR_SIZE);

		if (MVS_CHIP_DISP->phy_work_around)
			MVS_CHIP_DISP->phy_work_around(mvi, i);
	}
	mv_dprintk("phy %d attach dev info is %x\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_info);
	mv_dprintk("phy %d attach sas addr is %llx\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_sas_addr);
out_done:
	if (get_st)
		MVS_CHIP_DISP->write_port_irq_stat(mvi, i, phy->irq_status);
}