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
typedef  int u32 ;
struct lx_rmh {scalar_t__ dsp_stat; int stat_len; int /*<<< orphan*/  stat; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmd; } ;
struct lx6464es {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
#define  ED_DSP_CRASHED 129 
#define  ED_DSP_TIMED_OUT 128 
 int ERROR_VALUE ; 
 int ETIMEDOUT ; 
 int REG_CRM_NUMBER ; 
 int Reg_CSM_MC ; 
 int Reg_CSM_MR ; 
 int XILINX_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  eReg_CRM1 ; 
 int /*<<< orphan*/  eReg_CRM2 ; 
 int /*<<< orphan*/  eReg_CSM ; 
 int lx_dsp_reg_read (struct lx6464es*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_dsp_reg_readbuf (struct lx6464es*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lx_dsp_reg_write (struct lx6464es*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lx_dsp_reg_writebuf (struct lx6464es*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_message_dump (struct lx_rmh*) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int lx_message_send_atomic(struct lx6464es *chip, struct lx_rmh *rmh)
{
	u32 reg = ED_DSP_TIMED_OUT;
	int dwloop;

	if (lx_dsp_reg_read(chip, eReg_CSM) & (Reg_CSM_MC | Reg_CSM_MR)) {
		dev_err(chip->card->dev, "PIOSendMessage eReg_CSM %x\n", reg);
		return -EBUSY;
	}

	/* write command */
	lx_dsp_reg_writebuf(chip, eReg_CRM1, rmh->cmd, rmh->cmd_len);

	/* MicoBlaze gogogo */
	lx_dsp_reg_write(chip, eReg_CSM, Reg_CSM_MC);

	/* wait for device to answer */
	for (dwloop = 0; dwloop != XILINX_TIMEOUT_MS * 1000; ++dwloop) {
		if (lx_dsp_reg_read(chip, eReg_CSM) & Reg_CSM_MR) {
			if (rmh->dsp_stat == 0)
				reg = lx_dsp_reg_read(chip, eReg_CRM1);
			else
				reg = 0;
			goto polling_successful;
		} else
			udelay(1);
	}
	dev_warn(chip->card->dev, "TIMEOUT lx_message_send_atomic! "
		   "polling failed\n");

polling_successful:
	if ((reg & ERROR_VALUE) == 0) {
		/* read response */
		if (rmh->stat_len) {
			snd_BUG_ON(rmh->stat_len >= (REG_CRM_NUMBER-1));
			lx_dsp_reg_readbuf(chip, eReg_CRM2, rmh->stat,
					   rmh->stat_len);
		}
	} else
		dev_err(chip->card->dev, "rmh error: %08x\n", reg);

	/* clear Reg_CSM_MR */
	lx_dsp_reg_write(chip, eReg_CSM, 0);

	switch (reg) {
	case ED_DSP_TIMED_OUT:
		dev_warn(chip->card->dev, "lx_message_send: dsp timeout\n");
		return -ETIMEDOUT;

	case ED_DSP_CRASHED:
		dev_warn(chip->card->dev, "lx_message_send: dsp crashed\n");
		return -EAGAIN;
	}

	lx_message_dump(rmh);

	return reg;
}