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

/* Variables and functions */
#define  CS4231_ADPCM_16 130 
#define  CS4231_LINEAR_16 129 
#define  CS4231_LINEAR_16_BIG 128 
 unsigned char CS4231_STEREO ; 

__attribute__((used)) static unsigned int snd_wss_get_count(unsigned char format, unsigned int size)
{
	switch (format & 0xe0) {
	case CS4231_LINEAR_16:
	case CS4231_LINEAR_16_BIG:
		size >>= 1;
		break;
	case CS4231_ADPCM_16:
		return size >> 2;
	}
	if (format & CS4231_STEREO)
		size >>= 1;
	return size;
}