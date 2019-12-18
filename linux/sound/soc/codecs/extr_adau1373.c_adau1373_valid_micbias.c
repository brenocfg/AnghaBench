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
typedef  enum adau1373_micbias_voltage { ____Placeholder_adau1373_micbias_voltage } adau1373_micbias_voltage ;

/* Variables and functions */
#define  ADAU1373_MICBIAS_1_8V 131 
#define  ADAU1373_MICBIAS_2_2V 130 
#define  ADAU1373_MICBIAS_2_6V 129 
#define  ADAU1373_MICBIAS_2_9V 128 

__attribute__((used)) static bool adau1373_valid_micbias(enum adau1373_micbias_voltage micbias)
{
	switch (micbias) {
	case ADAU1373_MICBIAS_2_9V:
	case ADAU1373_MICBIAS_2_2V:
	case ADAU1373_MICBIAS_2_6V:
	case ADAU1373_MICBIAS_1_8V:
		return true;
	default:
		break;
	}
	return false;
}