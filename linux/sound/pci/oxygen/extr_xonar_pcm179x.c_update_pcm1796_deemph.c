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
typedef  int u8 ;
struct xonar_pcm179x {int** pcm1796_regs; int current_rate; unsigned int dacs; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int PCM1796_DMF_32 ; 
 int PCM1796_DMF_441 ; 
 int PCM1796_DMF_48 ; 
 int PCM1796_DMF_MASK ; 
 int PCM1796_REG_BASE ; 
 int /*<<< orphan*/  pcm1796_write_cached (struct oxygen*,unsigned int,int,int) ; 

__attribute__((used)) static void update_pcm1796_deemph(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;
	u8 reg;

	reg = data->pcm1796_regs[0][18 - PCM1796_REG_BASE] & ~PCM1796_DMF_MASK;
	if (data->current_rate == 48000)
		reg |= PCM1796_DMF_48;
	else if (data->current_rate == 44100)
		reg |= PCM1796_DMF_441;
	else if (data->current_rate == 32000)
		reg |= PCM1796_DMF_32;
	for (i = 0; i < data->dacs; ++i)
		pcm1796_write_cached(chip, i, 18, reg);
}