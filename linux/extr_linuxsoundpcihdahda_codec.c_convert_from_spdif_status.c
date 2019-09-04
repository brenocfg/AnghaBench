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
 unsigned short AC_DIG1_COPYRIGHT ; 
 unsigned short AC_DIG1_EMPHASIS ; 
 unsigned short AC_DIG1_LEVEL ; 
 unsigned short AC_DIG1_NONAUDIO ; 
 unsigned short AC_DIG1_PROFESSIONAL ; 
 unsigned int IEC958_AES0_CON_EMPHASIS ; 
 unsigned int IEC958_AES0_CON_EMPHASIS_5015 ; 
 unsigned int IEC958_AES0_CON_NOT_COPYRIGHT ; 
 unsigned int IEC958_AES0_NONAUDIO ; 
 unsigned int IEC958_AES0_PROFESSIONAL ; 
 unsigned int IEC958_AES0_PRO_EMPHASIS ; 
 unsigned int IEC958_AES0_PRO_EMPHASIS_5015 ; 
 int IEC958_AES1_CON_CATEGORY ; 
 int IEC958_AES1_CON_ORIGINAL ; 

__attribute__((used)) static unsigned short convert_from_spdif_status(unsigned int sbits)
{
	unsigned short val = 0;

	if (sbits & IEC958_AES0_PROFESSIONAL)
		val |= AC_DIG1_PROFESSIONAL;
	if (sbits & IEC958_AES0_NONAUDIO)
		val |= AC_DIG1_NONAUDIO;
	if (sbits & IEC958_AES0_PROFESSIONAL) {
		if ((sbits & IEC958_AES0_PRO_EMPHASIS) ==
		    IEC958_AES0_PRO_EMPHASIS_5015)
			val |= AC_DIG1_EMPHASIS;
	} else {
		if ((sbits & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			val |= AC_DIG1_EMPHASIS;
		if (!(sbits & IEC958_AES0_CON_NOT_COPYRIGHT))
			val |= AC_DIG1_COPYRIGHT;
		if (sbits & (IEC958_AES1_CON_ORIGINAL << 8))
			val |= AC_DIG1_LEVEL;
		val |= sbits & (IEC958_AES1_CON_CATEGORY << 8);
	}
	return val;
}