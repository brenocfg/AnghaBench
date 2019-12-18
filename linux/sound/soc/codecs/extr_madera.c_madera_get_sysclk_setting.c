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
 int EINVAL ; 
 int MADERA_SYSCLK_12MHZ ; 
 int MADERA_SYSCLK_24MHZ ; 
 int MADERA_SYSCLK_49MHZ ; 
 int MADERA_SYSCLK_98MHZ ; 
 int MADERA_SYSCLK_FREQ_SHIFT ; 

__attribute__((used)) static int madera_get_sysclk_setting(unsigned int freq)
{
	switch (freq) {
	case 0:
	case 5644800:
	case 6144000:
		return 0;
	case 11289600:
	case 12288000:
		return MADERA_SYSCLK_12MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	case 22579200:
	case 24576000:
		return MADERA_SYSCLK_24MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	case 45158400:
	case 49152000:
		return MADERA_SYSCLK_49MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	case 90316800:
	case 98304000:
		return MADERA_SYSCLK_98MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	default:
		return -EINVAL;
	}
}