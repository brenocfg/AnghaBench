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
struct pcxhr_rmh {unsigned int* cmd; int cmd_len; } ;
struct pcxhr_mgr {int use_clock_type; TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 int EINVAL ; 
 unsigned int IO_NUM_REG_GENCLK ; 
 unsigned int MASK_DSP_WORD ; 
#define  PCXHR_CLOCK_TYPE_AES_1 134 
#define  PCXHR_CLOCK_TYPE_AES_2 133 
#define  PCXHR_CLOCK_TYPE_AES_3 132 
#define  PCXHR_CLOCK_TYPE_AES_4 131 
#define  PCXHR_CLOCK_TYPE_AES_SYNC 130 
#define  PCXHR_CLOCK_TYPE_INTERNAL 129 
#define  PCXHR_CLOCK_TYPE_WORD_CLOCK 128 
 unsigned int PCXHR_FREQ_AES_1 ; 
 unsigned int PCXHR_FREQ_AES_2 ; 
 unsigned int PCXHR_FREQ_AES_3 ; 
 unsigned int PCXHR_FREQ_AES_4 ; 
 unsigned int PCXHR_FREQ_PLL ; 
 unsigned int PCXHR_FREQ_QUARTZ_11025 ; 
 unsigned int PCXHR_FREQ_QUARTZ_12000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_128000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_16000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_176400 ; 
 unsigned int PCXHR_FREQ_QUARTZ_192000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_22050 ; 
 unsigned int PCXHR_FREQ_QUARTZ_24000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_32000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_44100 ; 
 unsigned int PCXHR_FREQ_QUARTZ_48000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_64000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_8000 ; 
 unsigned int PCXHR_FREQ_QUARTZ_88200 ; 
 unsigned int PCXHR_FREQ_QUARTZ_96000 ; 
 unsigned int PCXHR_FREQ_SYNC_AES ; 
 unsigned int PCXHR_FREQ_WORD_CLOCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_pll_freq_register (unsigned int,unsigned int*,unsigned int*) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 

__attribute__((used)) static int pcxhr_get_clock_reg(struct pcxhr_mgr *mgr, unsigned int rate,
			       unsigned int *reg, unsigned int *freq)
{
	unsigned int val, realfreq, pllreg;
	struct pcxhr_rmh rmh;
	int err;

	realfreq = rate;
	switch (mgr->use_clock_type) {
	case PCXHR_CLOCK_TYPE_INTERNAL :	/* clock by quartz or pll */
		switch (rate) {
		case 48000 :	val = PCXHR_FREQ_QUARTZ_48000;	break;
		case 24000 :	val = PCXHR_FREQ_QUARTZ_24000;	break;
		case 12000 :	val = PCXHR_FREQ_QUARTZ_12000;	break;
		case 32000 :	val = PCXHR_FREQ_QUARTZ_32000;	break;
		case 16000 :	val = PCXHR_FREQ_QUARTZ_16000;	break;
		case 8000 :	val = PCXHR_FREQ_QUARTZ_8000;	break;
		case 44100 :	val = PCXHR_FREQ_QUARTZ_44100;	break;
		case 22050 :	val = PCXHR_FREQ_QUARTZ_22050;	break;
		case 11025 :	val = PCXHR_FREQ_QUARTZ_11025;	break;
		case 192000 :	val = PCXHR_FREQ_QUARTZ_192000;	break;
		case 96000 :	val = PCXHR_FREQ_QUARTZ_96000;	break;
		case 176400 :	val = PCXHR_FREQ_QUARTZ_176400;	break;
		case 88200 :	val = PCXHR_FREQ_QUARTZ_88200;	break;
		case 128000 :	val = PCXHR_FREQ_QUARTZ_128000;	break;
		case 64000 :	val = PCXHR_FREQ_QUARTZ_64000;	break;
		default :
			val = PCXHR_FREQ_PLL;
			/* get the value for the pll register */
			err = pcxhr_pll_freq_register(rate, &pllreg, &realfreq);
			if (err)
				return err;
			pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
			rmh.cmd[0] |= IO_NUM_REG_GENCLK;
			rmh.cmd[1]  = pllreg & MASK_DSP_WORD;
			rmh.cmd[2]  = pllreg >> 24;
			rmh.cmd_len = 3;
			err = pcxhr_send_msg(mgr, &rmh);
			if (err < 0) {
				dev_err(&mgr->pci->dev,
					   "error CMD_ACCESS_IO_WRITE "
					   "for PLL register : %x!\n", err);
				return err;
			}
		}
		break;
	case PCXHR_CLOCK_TYPE_WORD_CLOCK:
		val = PCXHR_FREQ_WORD_CLOCK;
		break;
	case PCXHR_CLOCK_TYPE_AES_SYNC:
		val = PCXHR_FREQ_SYNC_AES;
		break;
	case PCXHR_CLOCK_TYPE_AES_1:
		val = PCXHR_FREQ_AES_1;
		break;
	case PCXHR_CLOCK_TYPE_AES_2:
		val = PCXHR_FREQ_AES_2;
		break;
	case PCXHR_CLOCK_TYPE_AES_3:
		val = PCXHR_FREQ_AES_3;
		break;
	case PCXHR_CLOCK_TYPE_AES_4:
		val = PCXHR_FREQ_AES_4;
		break;
	default:
		return -EINVAL;
	}
	*reg = val;
	*freq = realfreq;
	return 0;
}