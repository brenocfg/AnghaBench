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
struct cs5535audio {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_CODEC_CNTL ; 
 unsigned int ACC_CODEC_CNTL_RD_CMD ; 
 int /*<<< orphan*/  ACC_CODEC_STATUS ; 
 unsigned int CMD_NEW ; 
 unsigned int STS_NEW ; 
 unsigned int cs_readl (struct cs5535audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_writel (struct cs5535audio*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_till_cmd_acked (struct cs5535audio*,int) ; 

__attribute__((used)) static unsigned short snd_cs5535audio_codec_read(struct cs5535audio *cs5535au,
						 unsigned short reg)
{
	unsigned int regdata;
	unsigned int timeout;
	unsigned int val;

	regdata = ((unsigned int) reg) << 24;
	regdata |= ACC_CODEC_CNTL_RD_CMD;
	regdata |= CMD_NEW;

	cs_writel(cs5535au, ACC_CODEC_CNTL, regdata);
	wait_till_cmd_acked(cs5535au, 50);

	timeout = 50;
	do {
		val = cs_readl(cs5535au, ACC_CODEC_STATUS);
		if ((val & STS_NEW) && reg == (val >> 24))
			break;
		udelay(1);
	} while (--timeout);
	if (!timeout)
		dev_err(cs5535au->card->dev,
			"Failure reading codec reg 0x%x, Last value=0x%x\n",
			reg, val);

	return (unsigned short) val;
}