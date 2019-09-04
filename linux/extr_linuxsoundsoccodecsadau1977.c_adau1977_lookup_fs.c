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
 int ADAU1977_SAI_CTRL0_FS_128000_192000 ; 
 int ADAU1977_SAI_CTRL0_FS_16000_24000 ; 
 int ADAU1977_SAI_CTRL0_FS_32000_48000 ; 
 int ADAU1977_SAI_CTRL0_FS_64000_96000 ; 
 int ADAU1977_SAI_CTRL0_FS_8000_12000 ; 
 int EINVAL ; 

__attribute__((used)) static int adau1977_lookup_fs(unsigned int rate)
{
	if (rate >= 8000 && rate <= 12000)
		return ADAU1977_SAI_CTRL0_FS_8000_12000;
	else if (rate >= 16000 && rate <= 24000)
		return ADAU1977_SAI_CTRL0_FS_16000_24000;
	else if (rate >= 32000 && rate <= 48000)
		return ADAU1977_SAI_CTRL0_FS_32000_48000;
	else if (rate >= 64000 && rate <= 96000)
		return ADAU1977_SAI_CTRL0_FS_64000_96000;
	else if (rate >= 128000 && rate <= 192000)
		return ADAU1977_SAI_CTRL0_FS_128000_192000;
	else
		return -EINVAL;
}