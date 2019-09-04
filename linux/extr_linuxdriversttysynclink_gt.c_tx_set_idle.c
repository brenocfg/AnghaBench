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
struct slgt_info {int idle_mode; } ;

/* Variables and functions */
 unsigned short BIT4 ; 
 unsigned short BIT5 ; 
 unsigned short BIT6 ; 
#define  HDLC_TXIDLE_ALT_MARK_SPACE 132 
#define  HDLC_TXIDLE_ALT_ZEROS_ONES 131 
 int HDLC_TXIDLE_CUSTOM_16 ; 
 int HDLC_TXIDLE_CUSTOM_8 ; 
#define  HDLC_TXIDLE_FLAGS 130 
#define  HDLC_TXIDLE_SPACE 129 
#define  HDLC_TXIDLE_ZEROS 128 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TIR ; 
 int /*<<< orphan*/  TPR ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg8 (struct slgt_info*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void tx_set_idle(struct slgt_info *info)
{
	unsigned char val;
	unsigned short tcr;

	/* if preamble enabled (tcr[6] == 1) then tx idle size = 8 bits
	 * else tcr[5:4] = tx idle size: 00 = 8 bits, 01 = 16 bits
	 */
	tcr = rd_reg16(info, TCR);
	if (info->idle_mode & HDLC_TXIDLE_CUSTOM_16) {
		/* disable preamble, set idle size to 16 bits */
		tcr = (tcr & ~(BIT6 + BIT5)) | BIT4;
		/* MSB of 16 bit idle specified in tx preamble register (TPR) */
		wr_reg8(info, TPR, (unsigned char)((info->idle_mode >> 8) & 0xff));
	} else if (!(tcr & BIT6)) {
		/* preamble is disabled, set idle size to 8 bits */
		tcr &= ~(BIT5 + BIT4);
	}
	wr_reg16(info, TCR, tcr);

	if (info->idle_mode & (HDLC_TXIDLE_CUSTOM_8 | HDLC_TXIDLE_CUSTOM_16)) {
		/* LSB of custom tx idle specified in tx idle register */
		val = (unsigned char)(info->idle_mode & 0xff);
	} else {
		/* standard 8 bit idle patterns */
		switch(info->idle_mode)
		{
		case HDLC_TXIDLE_FLAGS:          val = 0x7e; break;
		case HDLC_TXIDLE_ALT_ZEROS_ONES:
		case HDLC_TXIDLE_ALT_MARK_SPACE: val = 0xaa; break;
		case HDLC_TXIDLE_ZEROS:
		case HDLC_TXIDLE_SPACE:          val = 0x00; break;
		default:                         val = 0xff;
		}
	}

	wr_reg8(info, TIR, val);
}