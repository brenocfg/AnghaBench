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
struct sis_video_info {int caps; int engineok; } ;

/* Variables and functions */
 int AGP_CMD_QUEUE_CAP ; 
 int MMIO_CMD_QUEUE_CAP ; 
 int TURBO_QUEUE_CAP ; 
 int VM_CMD_QUEUE_CAP ; 

__attribute__((used)) static void
sisfb_engine_init(struct sis_video_info *ivideo)
{

	/* Initialize command queue (we use MMIO only) */

	/* BEFORE THIS IS CALLED, THE ENGINES *MUST* BE SYNC'ED */

	ivideo->caps &= ~(TURBO_QUEUE_CAP    |
			  MMIO_CMD_QUEUE_CAP |
			  VM_CMD_QUEUE_CAP   |
			  AGP_CMD_QUEUE_CAP);

#ifdef CONFIG_FB_SIS_300
	if(ivideo->sisvga_engine == SIS_300_VGA) {
		u32 tqueue_pos;
		u8 tq_state;

		tqueue_pos = (ivideo->video_size - ivideo->cmdQueueSize) / (64 * 1024);

		tq_state = SiS_GetReg(SISSR, IND_SIS_TURBOQUEUE_SET);
		tq_state |= 0xf0;
		tq_state &= 0xfc;
		tq_state |= (u8)(tqueue_pos >> 8);
		SiS_SetReg(SISSR, IND_SIS_TURBOQUEUE_SET, tq_state);

		SiS_SetReg(SISSR, IND_SIS_TURBOQUEUE_ADR, (u8)(tqueue_pos & 0xff));

		ivideo->caps |= TURBO_QUEUE_CAP;
	}
#endif

#ifdef CONFIG_FB_SIS_315
	if(ivideo->sisvga_engine == SIS_315_VGA) {
		u32 tempq = 0, templ;
		u8  temp;

		if(ivideo->chip == XGI_20) {
			switch(ivideo->cmdQueueSize) {
			case (64 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_Z7_64k;
				break;
			case (128 * 1024):
			default:
				temp = SIS_CMD_QUEUE_SIZE_Z7_128k;
			}
		} else {
			switch(ivideo->cmdQueueSize) {
			case (4 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_4M;
				break;
			case (2 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_2M;
				break;
			case (1 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_1M;
				break;
			default:
			case (512 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_512k;
			}
		}

		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_THRESHOLD, COMMAND_QUEUE_THRESHOLD);
		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, SIS_CMD_QUEUE_RESET);

		if((ivideo->chip >= XGI_40) && ivideo->modechanged) {
			/* Must disable dual pipe on XGI_40. Can't do
			 * this in MMIO mode, because it requires
			 * setting/clearing a bit in the MMIO fire trigger
			 * register.
			 */
			if(!((templ = MMIO_IN32(ivideo->mmio_vbase, 0x8240)) & (1 << 10))) {

				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, 0);

				SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, (temp | SIS_VRAM_CMDQUEUE_ENABLE));

				tempq = MMIO_IN32(ivideo->mmio_vbase, Q_READ_PTR);
				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, tempq);

				tempq = (u32)(ivideo->video_size - ivideo->cmdQueueSize);
				MMIO_OUT32(ivideo->mmio_vbase, Q_BASE_ADDR, tempq);

				writel(0x16800000 + 0x8240, ivideo->video_vbase + tempq);
				writel(templ | (1 << 10), ivideo->video_vbase + tempq + 4);
				writel(0x168F0000, ivideo->video_vbase + tempq + 8);
				writel(0x168F0000, ivideo->video_vbase + tempq + 12);

				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, (tempq + 16));

				sisfb_syncaccel(ivideo);

				SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, SIS_CMD_QUEUE_RESET);

			}
		}

		tempq = MMIO_IN32(ivideo->mmio_vbase, MMIO_QUEUE_READPORT);
		MMIO_OUT32(ivideo->mmio_vbase, MMIO_QUEUE_WRITEPORT, tempq);

		temp |= (SIS_MMIO_CMD_ENABLE | SIS_CMD_AUTO_CORR);
		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, temp);

		tempq = (u32)(ivideo->video_size - ivideo->cmdQueueSize);
		MMIO_OUT32(ivideo->mmio_vbase, MMIO_QUEUE_PHYBASE, tempq);

		ivideo->caps |= MMIO_CMD_QUEUE_CAP;
	}
#endif

	ivideo->engineok = 1;
}