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
struct SiS_Private {int SiS_DDC_DeviceAddr; unsigned short SiS_DDC_ReadAddr; int SiS_ChrontelInit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_DDC2Delay (struct SiS_Private*,int) ; 
 int SiS_I2CDELAYSHORT ; 
 unsigned short SiS_ReadDDC2Data (struct SiS_Private*) ; 
 scalar_t__ SiS_SetStart (struct SiS_Private*) ; 
 scalar_t__ SiS_SetStop (struct SiS_Private*) ; 
 unsigned short SiS_WriteDDC2Data (struct SiS_Private*,int) ; 

__attribute__((used)) static unsigned short
SiS_GetChReg(struct SiS_Private *SiS_Pr, unsigned short myor)
{
  unsigned short tempah, temp, i;

  for(i=0; i<20; i++) {				/* Do 20 attempts to read */
     if(i) {
	SiS_SetStop(SiS_Pr);
	SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT * 4);
     }
     if(SiS_SetStart(SiS_Pr)) continue;					/* Set start condition */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_DeviceAddr);	/* Write DAB (S0=0=write) */
     if(temp) continue;							/*        (ERROR: no ack) */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_ReadAddr | myor);	/* Write RAB (700x: | 0x80) */
     if(temp) continue;							/*        (ERROR: no ack) */
     if (SiS_SetStart(SiS_Pr)) continue;				/* Re-start */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_DeviceAddr | 0x01);/* DAB (S0=1=read) */
     if(temp) continue;							/*        (ERROR: no ack) */
     tempah = SiS_ReadDDC2Data(SiS_Pr);					/* Read byte */
     if(SiS_SetStop(SiS_Pr)) continue;					/* Stop condition */
     SiS_Pr->SiS_ChrontelInit = 1;
     return tempah;
  }
  return 0xFFFF;
}