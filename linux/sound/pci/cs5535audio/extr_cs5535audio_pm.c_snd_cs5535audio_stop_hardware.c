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
 int /*<<< orphan*/  ACC_CODEC_CNTL_LNK_SHUTDOWN ; 
 int /*<<< orphan*/  cs_writel (struct cs5535audio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_cs5535audio_stop_hardware(struct cs5535audio *cs5535au)
{
	/* 
	we depend on snd_ac97_suspend to tell the
	AC97 codec to shutdown. the amd spec suggests
	that the LNK_SHUTDOWN be done at the same time
	that the codec power-down is issued. instead,
	we do it just after rather than at the same 
	time. excluding codec specific build_ops->suspend
	ac97 powerdown hits:
	0x8000 EAPD 
	0x4000 Headphone amplifier 
	0x0300 ADC & DAC 
	0x0400 Analog Mixer powerdown (Vref on) 
	I am not sure if this is the best that we can do.
	The remainder to be investigated are:
	- analog mixer (vref off) 0x0800
	- AC-link powerdown 0x1000
	- codec internal clock 0x2000
	*/

	/* set LNK_SHUTDOWN to shutdown AC link */
	cs_writel(cs5535au, ACC_CODEC_CNTL, ACC_CODEC_CNTL_LNK_SHUTDOWN);

}