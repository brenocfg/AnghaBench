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
struct pcxhr_mgr {int board_has_analog; int board_has_mic; int dsp_reset; TYPE_1__* pci; int /*<<< orphan*/  xlx_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AKM_CLOCK_INF_55K_CMD ; 
 int /*<<< orphan*/  AKM_POWER_CONTROL_CMD ; 
 int /*<<< orphan*/  AKM_RESET_OFF_CMD ; 
 int /*<<< orphan*/  AKM_UNMUTE_CMD ; 
 int /*<<< orphan*/  PCXHR_CFG_SYNCDSP_MASK ; 
 int /*<<< orphan*/  PCXHR_DSP_RESET ; 
 int PCXHR_DSP_RESET_CODEC ; 
 int PCXHR_DSP_RESET_DSP ; 
 int PCXHR_DSP_RESET_MUTE ; 
 unsigned char PCXHR_INPB (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int) ; 
 unsigned char PCXHR_STAT_MIC_CAPS ; 
 int /*<<< orphan*/  PCXHR_XLX_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hr222_config_akm (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hr222_micro_boost (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

int hr222_sub_init(struct pcxhr_mgr *mgr)
{
	unsigned char reg;

	mgr->board_has_analog = 1;	/* analog always available */
	mgr->xlx_cfg = PCXHR_CFG_SYNCDSP_MASK;

	reg = PCXHR_INPB(mgr, PCXHR_XLX_STATUS);
	if (reg & PCXHR_STAT_MIC_CAPS)
		mgr->board_has_mic = 1;	/* microphone available */
	dev_dbg(&mgr->pci->dev,
		"MIC input available = %d\n", mgr->board_has_mic);

	/* reset codec */
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET,
		    PCXHR_DSP_RESET_DSP);
	msleep(5);
	mgr->dsp_reset = PCXHR_DSP_RESET_DSP  |
			 PCXHR_DSP_RESET_MUTE |
			 PCXHR_DSP_RESET_CODEC;
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, mgr->dsp_reset);
	/* hr222_write_gpo(mgr, 0); does the same */
	msleep(5);

	/* config AKM */
	hr222_config_akm(mgr, AKM_POWER_CONTROL_CMD);
	hr222_config_akm(mgr, AKM_CLOCK_INF_55K_CMD);
	hr222_config_akm(mgr, AKM_UNMUTE_CMD);
	hr222_config_akm(mgr, AKM_RESET_OFF_CMD);

	/* init micro boost */
	hr222_micro_boost(mgr, 0);

	return 0;
}