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
struct snd_aes_iec958 {int* status; } ;

/* Variables and functions */
 int IEC958_AES0_CON_EMPHASIS_5015 ; 
 int IEC958_AES0_NONAUDIO ; 
 int IEC958_AES0_PROFESSIONAL ; 
 int IEC958_AES0_PRO_EMPHASIS_5015 ; 
 int RME96_WCR_DOLBY ; 
 int RME96_WCR_EMP ; 
 int RME96_WCR_PRO ; 

__attribute__((used)) static u32 snd_rme96_convert_from_aes(struct snd_aes_iec958 *aes)
{
	u32 val = 0;
	val |= (aes->status[0] & IEC958_AES0_PROFESSIONAL) ? RME96_WCR_PRO : 0;
	val |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? RME96_WCR_DOLBY : 0;
	if (val & RME96_WCR_PRO)
		val |= (aes->status[0] & IEC958_AES0_PRO_EMPHASIS_5015) ? RME96_WCR_EMP : 0;
	else
		val |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? RME96_WCR_EMP : 0;
	return val;
}