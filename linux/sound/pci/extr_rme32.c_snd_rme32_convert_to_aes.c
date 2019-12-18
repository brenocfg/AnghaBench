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
struct snd_aes_iec958 {int /*<<< orphan*/ * status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEC958_AES0_CON_EMPHASIS_5015 ; 
 int /*<<< orphan*/  IEC958_AES0_PROFESSIONAL ; 
 int /*<<< orphan*/  IEC958_AES0_PRO_EMPHASIS_5015 ; 
 int RME32_WCR_EMP ; 
 int RME32_WCR_PRO ; 

__attribute__((used)) static void snd_rme32_convert_to_aes(struct snd_aes_iec958 * aes, u32 val)
{
	aes->status[0] = ((val & RME32_WCR_PRO) ? IEC958_AES0_PROFESSIONAL : 0);
	if (val & RME32_WCR_PRO)
		aes->status[0] |= (val & RME32_WCR_EMP) ? IEC958_AES0_PRO_EMPHASIS_5015 : 0;
	else
		aes->status[0] |= (val & RME32_WCR_EMP) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
}