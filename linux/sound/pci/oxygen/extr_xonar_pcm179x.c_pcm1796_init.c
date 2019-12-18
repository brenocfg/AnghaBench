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
struct xonar_pcm179x {int** pcm1796_regs; int current_rate; scalar_t__ h6; int /*<<< orphan*/  broken_i2c; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int PCM1796_ATLD ; 
 int PCM1796_ATS_1 ; 
 int PCM1796_FLT_SHARP ; 
 int PCM1796_FMT_24_I2S ; 
 int PCM1796_MUTE ; 
 int PCM1796_OS_128 ; 
 int PCM1796_OS_64 ; 
 int PCM1796_REG_BASE ; 
 int /*<<< orphan*/  pcm1796_registers_init (struct oxygen*) ; 

__attribute__((used)) static void pcm1796_init(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;

	data->pcm1796_regs[0][18 - PCM1796_REG_BASE] =
		PCM1796_FMT_24_I2S | PCM1796_ATLD;
	if (!data->broken_i2c)
		data->pcm1796_regs[0][18 - PCM1796_REG_BASE] |= PCM1796_MUTE;
	data->pcm1796_regs[0][19 - PCM1796_REG_BASE] =
		PCM1796_FLT_SHARP | PCM1796_ATS_1;
	data->pcm1796_regs[0][20 - PCM1796_REG_BASE] =
		data->h6 ? PCM1796_OS_64 : PCM1796_OS_128;
	pcm1796_registers_init(chip);
	data->current_rate = 48000;
}