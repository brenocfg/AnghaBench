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
struct pcxhr_rmh {int cmd_len; int* cmd; size_t cmd_idx; } ;
struct pcxhr_mgr {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CMD_LAST_INDEX ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PCXHR_DSP_ISR ; 
 int /*<<< orphan*/  PCXHR_DSP_TXH ; 
 int /*<<< orphan*/  PCXHR_DSP_TXL ; 
 int /*<<< orphan*/  PCXHR_DSP_TXM ; 
 int PCXHR_INPB (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_ISR_HI08_CHK ; 
 unsigned char PCXHR_ISR_HI08_ERR ; 
 int /*<<< orphan*/  PCXHR_ISR_HI08_RXDF ; 
 int /*<<< orphan*/  PCXHR_ISR_HI08_TRDY ; 
 int /*<<< orphan*/  PCXHR_IT_MESSAGE ; 
 int /*<<< orphan*/  PCXHR_IT_RESET_CHK ; 
 int /*<<< orphan*/  PCXHR_IT_RESET_SEMAPHORE ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int) ; 
 int PCXHR_SIZE_MAX_CMD ; 
 int /*<<< orphan*/  PCXHR_TIMEOUT_DSP ; 
 int* cmd_names ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int pcxhr_check_reg_bit (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int pcxhr_read_rmh_status (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int pcxhr_send_it_dsp (struct pcxhr_mgr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int pcxhr_send_msg_nolock(struct pcxhr_mgr *mgr, struct pcxhr_rmh *rmh)
{
	int err;
	int i;
	u32 data;
	unsigned char reg;

	if (snd_BUG_ON(rmh->cmd_len >= PCXHR_SIZE_MAX_CMD))
		return -EINVAL;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_MESSAGE, 1);
	if (err) {
		dev_err(&mgr->pci->dev,
			"pcxhr_send_message : ED_DSP_CRASHED\n");
		return err;
	}
	/* wait for chk bit */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK,
				  PCXHR_ISR_HI08_CHK, PCXHR_TIMEOUT_DSP, &reg);
	if (err)
		return err;
	/* reset irq chk */
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_CHK, 1);
	if (err)
		return err;
	/* wait for chk bit == 0*/
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK, 0,
				  PCXHR_TIMEOUT_DSP, &reg);
	if (err)
		return err;

	data = rmh->cmd[0];

	if (rmh->cmd_len > 1)
		data |= 0x008000;	/* MASK_MORE_THAN_1_WORD_COMMAND */
	else
		data &= 0xff7fff;	/* MASK_1_WORD_COMMAND */
#ifdef CONFIG_SND_DEBUG_VERBOSE
	if (rmh->cmd_idx < CMD_LAST_INDEX)
		dev_dbg(&mgr->pci->dev, "MSG cmd[0]=%x (%s)\n",
			    data, cmd_names[rmh->cmd_idx]);
#endif

	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_TRDY,
				  PCXHR_ISR_HI08_TRDY, PCXHR_TIMEOUT_DSP, &reg);
	if (err)
		return err;
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));

	if (rmh->cmd_len > 1) {
		/* send length */
		data = rmh->cmd_len - 1;
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_TIMEOUT_DSP, &reg);
		if (err)
			return err;
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));

		for (i=1; i < rmh->cmd_len; i++) {
			/* send other words */
			data = rmh->cmd[i];
#ifdef CONFIG_SND_DEBUG_VERBOSE
			if (rmh->cmd_idx < CMD_LAST_INDEX)
				dev_dbg(&mgr->pci->dev,
					"    cmd[%d]=%x\n", i, data);
#endif
			err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
						  PCXHR_ISR_HI08_TRDY,
						  PCXHR_ISR_HI08_TRDY,
						  PCXHR_TIMEOUT_DSP, &reg);
			if (err)
				return err;
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));
		}
	}
	/* wait for chk bit */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK,
				  PCXHR_ISR_HI08_CHK, PCXHR_TIMEOUT_DSP, &reg);
	if (err)
		return err;
	/* test status ISR */
	if (reg & PCXHR_ISR_HI08_ERR) {
		/* ERROR, wait for receiver full */
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_TIMEOUT_DSP, &reg);
		if (err) {
			dev_err(&mgr->pci->dev,
				"ERROR RMH: ISR:RXDF=1 (ISR = %x)\n", reg);
			return err;
		}
		/* read error code */
		data  = PCXHR_INPB(mgr, PCXHR_DSP_TXH) << 16;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXM) << 8;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXL);
		dev_err(&mgr->pci->dev, "ERROR RMH(%d): 0x%x\n",
			   rmh->cmd_idx, data);
		err = -EINVAL;
	} else {
		/* read the response data */
		err = pcxhr_read_rmh_status(mgr, rmh);
	}
	/* reset semaphore */
	if (pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_SEMAPHORE, 1) < 0)
		return -EIO;
	return err;
}