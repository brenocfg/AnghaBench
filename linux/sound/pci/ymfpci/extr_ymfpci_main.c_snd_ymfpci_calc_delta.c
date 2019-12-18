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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 snd_ymfpci_calc_delta(u32 rate)
{
	switch (rate) {
	case 8000:	return 0x02aaab00;
	case 11025:	return 0x03accd00;
	case 16000:	return 0x05555500;
	case 22050:	return 0x07599a00;
	case 32000:	return 0x0aaaab00;
	case 44100:	return 0x0eb33300;
	default:	return ((rate << 16) / 375) << 5;
	}
}