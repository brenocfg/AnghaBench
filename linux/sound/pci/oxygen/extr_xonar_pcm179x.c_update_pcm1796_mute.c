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
typedef  int /*<<< orphan*/  u8 ;
struct xonar_pcm179x {unsigned int dacs; int /*<<< orphan*/ ** pcm1796_regs; } ;
struct oxygen {scalar_t__ dac_mute; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM1796_MUTE ; 
 int PCM1796_REG_BASE ; 
 int /*<<< orphan*/  pcm1796_write_cached (struct oxygen*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_pcm1796_mute(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;
	u8 value;

	value = data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	if (chip->dac_mute)
		value |= PCM1796_MUTE;
	else
		value &= ~PCM1796_MUTE;
	for (i = 0; i < data->dacs; ++i)
		pcm1796_write_cached(chip, i, 18, value);
}