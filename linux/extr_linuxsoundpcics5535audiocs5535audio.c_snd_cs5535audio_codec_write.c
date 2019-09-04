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
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_CODEC_CNTL ; 
 unsigned int ACC_CODEC_CNTL_WR_CMD ; 
 unsigned int CMD_MASK ; 
 unsigned int CMD_NEW ; 
 int /*<<< orphan*/  cs_writel (struct cs5535audio*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wait_till_cmd_acked (struct cs5535audio*,int) ; 

__attribute__((used)) static void snd_cs5535audio_codec_write(struct cs5535audio *cs5535au,
					unsigned short reg, unsigned short val)
{
	unsigned int regdata;

	regdata = ((unsigned int) reg) << 24;
	regdata |= val;
	regdata &= CMD_MASK;
	regdata |= CMD_NEW;
	regdata &= ACC_CODEC_CNTL_WR_CMD;

	cs_writel(cs5535au, ACC_CODEC_CNTL, regdata);
	wait_till_cmd_acked(cs5535au, 50);
}