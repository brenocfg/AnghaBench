#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {int SiS_TVMode; scalar_t__ SiS_ModeType; int SiS_IF_DEF_CH70xx; struct SiS_CHTVRegData* SiS_CHTVReg_OPAL; struct SiS_CHTVRegData* SiS_CHTVReg_SOPAL; struct SiS_CHTVRegData* SiS_CHTVReg_OPALN; struct SiS_CHTVRegData* SiS_CHTVReg_UPALN; struct SiS_CHTVRegData* SiS_CHTVReg_OPALM; struct SiS_CHTVRegData* SiS_CHTVReg_UPALM; struct SiS_CHTVRegData* SiS_CHTVReg_UPAL; struct SiS_CHTVRegData* SiS_CHTVReg_ONTSC; struct SiS_CHTVRegData* SiS_CHTVReg_UNTSC; scalar_t__ SiS_CHSOverScan; TYPE_2__* SiS_RefIndex; TYPE_1__* SiS_SModeIDTable; } ;
struct SiS_CHTVRegData {int dummy; } ;
struct TYPE_4__ {unsigned short Ext_CRT2CRTC; } ;
struct TYPE_3__ {unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 scalar_t__ ModeVGA ; 
 int TVSetCHOverScan ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetPALN ; 

__attribute__((used)) static void
SiS_SetCHTVReg(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
               unsigned short RefreshRateTableIndex)
{
   unsigned short TVType, resindex;
   const struct SiS_CHTVRegData *CHTVRegData = NULL;

   if(ModeNo <= 0x13)
      resindex = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
   else
      resindex = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;

   resindex &= 0x3F;

   TVType = 0;
   if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
   if(SiS_Pr->SiS_TVMode & TVSetPAL) {
      TVType += 2;
      if(SiS_Pr->SiS_ModeType > ModeVGA) {
	 if(SiS_Pr->SiS_CHSOverScan) TVType = 8;
      }
      if(SiS_Pr->SiS_TVMode & TVSetPALM) {
	 TVType = 4;
	 if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
      } else if(SiS_Pr->SiS_TVMode & TVSetPALN) {
	 TVType = 6;
	 if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
      }
   }

   switch(TVType) {
      case  0: CHTVRegData = SiS_Pr->SiS_CHTVReg_UNTSC; break;
      case  1: CHTVRegData = SiS_Pr->SiS_CHTVReg_ONTSC; break;
      case  2: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPAL;  break;
      case  3: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPAL;  break;
      case  4: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPALM; break;
      case  5: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPALM; break;
      case  6: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPALN; break;
      case  7: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPALN; break;
      case  8: CHTVRegData = SiS_Pr->SiS_CHTVReg_SOPAL; break;
      default: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPAL;  break;
   }


   if(SiS_Pr->SiS_IF_DEF_CH70xx == 1) {

#ifdef CONFIG_FB_SIS_300

      /* Chrontel 7005 - I assume that it does not come with a 315 series chip */

      /* We don't support modes >800x600 */
      if (resindex > 5) return;

      if(SiS_Pr->SiS_TVMode & TVSetPAL) {
	 SiS_SetCH700x(SiS_Pr,0x04,0x43);  /* 0x40=76uA (PAL); 0x03=15bit non-multi RGB*/
	 SiS_SetCH700x(SiS_Pr,0x09,0x69);  /* Black level for PAL (105)*/
      } else {
	 SiS_SetCH700x(SiS_Pr,0x04,0x03);   /* upper nibble=71uA (NTSC), 0x03=15bit non-multi RGB*/
	 SiS_SetCH700x(SiS_Pr,0x09,0x71);   /* Black level for NTSC (113)*/
      }

      SiS_SetCH700x(SiS_Pr,0x00,CHTVRegData[resindex].Reg[0]);	/* Mode register */
      SiS_SetCH700x(SiS_Pr,0x07,CHTVRegData[resindex].Reg[1]);	/* Start active video register */
      SiS_SetCH700x(SiS_Pr,0x08,CHTVRegData[resindex].Reg[2]);	/* Position overflow register */
      SiS_SetCH700x(SiS_Pr,0x0a,CHTVRegData[resindex].Reg[3]);	/* Horiz Position register */
      SiS_SetCH700x(SiS_Pr,0x0b,CHTVRegData[resindex].Reg[4]);	/* Vertical Position register */

      /* Set minimum flicker filter for Luma channel (SR1-0=00),
                minimum text enhancement (S3-2=10),
   	        maximum flicker filter for Chroma channel (S5-4=10)
	        =00101000=0x28 (When reading, S1-0->S3-2, and S3-2->S1-0!)
       */
      SiS_SetCH700x(SiS_Pr,0x01,0x28);

      /* Set video bandwidth
            High bandwidth Luma composite video filter(S0=1)
            low bandwidth Luma S-video filter (S2-1=00)
	    disable peak filter in S-video channel (S3=0)
	    high bandwidth Chroma Filter (S5-4=11)
	    =00110001=0x31
      */
      SiS_SetCH700x(SiS_Pr,0x03,0xb1);       /* old: 3103 */

      /* Register 0x3D does not exist in non-macrovision register map
            (Maybe this is a macrovision register?)
       */
#ifndef SIS_CP
      SiS_SetCH70xx(SiS_Pr,0x3d,0x00);
#endif

      /* Register 0x10 only contains 1 writable bit (S0) for sensing,
             all other bits a read-only. Macrovision?
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x10,0x00,0x1F);

      /* Register 0x11 only contains 3 writable bits (S0-S2) for
             contrast enhancement (set to 010 -> gain 1 Yout = 17/16*(Yin-30) )
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x11,0x02,0xF8);

      /* Clear DSEN
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x00,0xEF);

      if(!(SiS_Pr->SiS_TVMode & TVSetPAL)) {		/* ---- NTSC ---- */
         if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) {
            if(resindex == 0x04) {   			/* 640x480 overscan: Mode 16 */
      	       SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);	/* ACIV on, no need to set FSCI */
            } else if(resindex == 0x05) {    		/* 800x600 overscan: Mode 23 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x18,0x01,0xF0);	/* 0x18-0x1f: FSCI 469,762,048 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x19,0x0C,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1a,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1b,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1d,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1e,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1f,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x01,0xEF);	/* Loop filter on for mode 23 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x00,0xFE);	/* ACIV off, need to set FSCI */
            }
         } else {
            if(resindex == 0x04) {     			/* ----- 640x480 underscan; Mode 17 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);
            } else if(resindex == 0x05) {   		/* ----- 800x600 underscan: Mode 24 */
#if 0
               SiS_SetCH70xxANDOR(SiS_Pr,0x18,0x01,0xF0);	/* (FSCI was 0x1f1c71c7 - this is for mode 22) */
               SiS_SetCH70xxANDOR(SiS_Pr,0x19,0x09,0xF0);	/* FSCI for mode 24 is 428,554,851 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x1a,0x08,0xF0);       /* 198b3a63 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x1b,0x0b,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x04,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1d,0x01,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1e,0x06,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1f,0x05,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off for mode 24 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x00,0xFE);	* ACIV off, need to set FSCI */
#endif         /* All alternatives wrong (datasheet wrong?), don't use FSCI */
	       SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	 /* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);
            }
         }
      } else {						/* ---- PAL ---- */
	/* We don't play around with FSCI in PAL mode */
	SiS_SetCH70xxANDOR(SiS_Pr, 0x20, 0x00, 0xEF);	/* loop filter off */
	SiS_SetCH70xxANDOR(SiS_Pr, 0x21, 0x01, 0xFE);	/* ACIV on */
      }

#endif  /* 300 */

   } else {

      /* Chrontel 7019 - assumed that it does not come with a 300 series chip */

#ifdef CONFIG_FB_SIS_315

      unsigned short temp;

      /* We don't support modes >1024x768 */
      if (resindex > 6) return;

      temp = CHTVRegData[resindex].Reg[0];
      if(SiS_Pr->SiS_TVMode & TVSetNTSCJ) temp |= 0x10;
      SiS_SetCH701x(SiS_Pr,0x00,temp);

      SiS_SetCH701x(SiS_Pr,0x01,CHTVRegData[resindex].Reg[1]);
      SiS_SetCH701x(SiS_Pr,0x02,CHTVRegData[resindex].Reg[2]);
      SiS_SetCH701x(SiS_Pr,0x04,CHTVRegData[resindex].Reg[3]);
      SiS_SetCH701x(SiS_Pr,0x03,CHTVRegData[resindex].Reg[4]);
      SiS_SetCH701x(SiS_Pr,0x05,CHTVRegData[resindex].Reg[5]);
      SiS_SetCH701x(SiS_Pr,0x06,CHTVRegData[resindex].Reg[6]);

      temp = CHTVRegData[resindex].Reg[7];
      if(SiS_Pr->SiS_TVMode & TVSetNTSCJ) temp = 0x66;
      SiS_SetCH701x(SiS_Pr,0x07,temp);

      SiS_SetCH701x(SiS_Pr,0x08,CHTVRegData[resindex].Reg[8]);
      SiS_SetCH701x(SiS_Pr,0x15,CHTVRegData[resindex].Reg[9]);
      SiS_SetCH701x(SiS_Pr,0x1f,CHTVRegData[resindex].Reg[10]);
      SiS_SetCH701x(SiS_Pr,0x0c,CHTVRegData[resindex].Reg[11]);
      SiS_SetCH701x(SiS_Pr,0x0d,CHTVRegData[resindex].Reg[12]);
      SiS_SetCH701x(SiS_Pr,0x0e,CHTVRegData[resindex].Reg[13]);
      SiS_SetCH701x(SiS_Pr,0x0f,CHTVRegData[resindex].Reg[14]);
      SiS_SetCH701x(SiS_Pr,0x10,CHTVRegData[resindex].Reg[15]);

      temp = SiS_GetCH701x(SiS_Pr,0x21) & ~0x02;
      /* D1 should be set for PAL, PAL-N and NTSC-J,
         but I won't do that for PAL unless somebody
	 tells me to do so. Since the BIOS uses
	 non-default CIV values and blacklevels,
	 this might be compensated anyway.
       */
      if(SiS_Pr->SiS_TVMode & (TVSetPALN | TVSetNTSCJ)) temp |= 0x02;
      SiS_SetCH701x(SiS_Pr,0x21,temp);

#endif	/* 315 */

   }

#ifdef SIS_CP
   SIS_CP_INIT301_CP3
#endif

}