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
typedef  int /*<<< orphan*/  snd_pcm_format_t ;

/* Variables and functions */
 unsigned int I2S_WLEN_16_BIT ; 
 unsigned int I2S_WLEN_32_BIT ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_i2s_wlen(snd_pcm_format_t format)
{
	return snd_pcm_format_physical_width(format) <= 16 ?
	       I2S_WLEN_16_BIT : I2S_WLEN_32_BIT;
}