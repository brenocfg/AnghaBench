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
struct sis_video_info {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 

__attribute__((used)) static void SiS_SenseCh(struct sis_video_info *ivideo)
{
#if defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
    u8 temp1, temp2;
    char stdstr[] = "sisfb: Chrontel: Detected TV connected to";
#endif
#ifdef CONFIG_FB_SIS_300
    unsigned char test[3];
    int i;
#endif

    if(ivideo->chip < SIS_315H) {

#ifdef CONFIG_FB_SIS_300
       ivideo->SiS_Pr.SiS_IF_DEF_CH70xx = 1;		/* Chrontel 700x */
       SiS_SetChrontelGPIO(&ivideo->SiS_Pr, 0x9c);	/* Set general purpose IO for Chrontel communication */
       SiS_DDC2Delay(&ivideo->SiS_Pr, 1000);
       temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x25);
       /* See Chrontel TB31 for explanation */
       temp2 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0e);
       if(((temp2 & 0x07) == 0x01) || (temp2 & 0x04)) {
	  SiS_SetCH700x(&ivideo->SiS_Pr, 0x0e, 0x0b);
	  SiS_DDC2Delay(&ivideo->SiS_Pr, 300);
       }
       temp2 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x25);
       if(temp2 != temp1) temp1 = temp2;

       if((temp1 >= 0x22) && (temp1 <= 0x50)) {
	   /* Read power status */
	   temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0e);
	   if((temp1 & 0x03) != 0x03) {
		/* Power all outputs */
		SiS_SetCH700x(&ivideo->SiS_Pr, 0x0e,0x0b);
		SiS_DDC2Delay(&ivideo->SiS_Pr, 300);
	   }
	   /* Sense connected TV devices */
	   for(i = 0; i < 3; i++) {
	       SiS_SetCH700x(&ivideo->SiS_Pr, 0x10, 0x01);
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	       SiS_SetCH700x(&ivideo->SiS_Pr, 0x10, 0x00);
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	       temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x10);
	       if(!(temp1 & 0x08))       test[i] = 0x02;
	       else if(!(temp1 & 0x02))  test[i] = 0x01;
	       else                      test[i] = 0;
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	   }

	   if(test[0] == test[1])      temp1 = test[0];
	   else if(test[0] == test[2]) temp1 = test[0];
	   else if(test[1] == test[2]) temp1 = test[1];
	   else {
		printk(KERN_INFO
			"sisfb: TV detection unreliable - test results varied\n");
		temp1 = test[2];
	   }
	   if(temp1 == 0x02) {
		printk(KERN_INFO "%s SVIDEO output\n", stdstr);
		ivideo->vbflags |= TV_SVIDEO;
		SiS_SetRegOR(SISCR, 0x32, 0x02);
		SiS_SetRegAND(SISCR, 0x32, ~0x05);
	   } else if (temp1 == 0x01) {
		printk(KERN_INFO "%s CVBS output\n", stdstr);
		ivideo->vbflags |= TV_AVIDEO;
		SiS_SetRegOR(SISCR, 0x32, 0x01);
		SiS_SetRegAND(SISCR, 0x32, ~0x06);
	   } else {
		SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x0e, 0x01, 0xF8);
		SiS_SetRegAND(SISCR, 0x32, ~0x07);
	   }
       } else if(temp1 == 0) {
	  SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x0e, 0x01, 0xF8);
	  SiS_SetRegAND(SISCR, 0x32, ~0x07);
       }
       /* Set general purpose IO for Chrontel communication */
       SiS_SetChrontelGPIO(&ivideo->SiS_Pr, 0x00);
#endif

    } else {

#ifdef CONFIG_FB_SIS_315
	ivideo->SiS_Pr.SiS_IF_DEF_CH70xx = 2;		/* Chrontel 7019 */
	temp1 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x49);
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x49, 0x20);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x20);
	temp2 |= 0x01;
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x20, temp2);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 ^= 0x01;
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x20, temp2);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x20);
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x49, temp1);
	temp1 = 0;
	if(temp2 & 0x02) temp1 |= 0x01;
	if(temp2 & 0x10) temp1 |= 0x01;
	if(temp2 & 0x04) temp1 |= 0x02;
	if( (temp1 & 0x01) && (temp1 & 0x02) ) temp1 = 0x04;
	switch(temp1) {
	case 0x01:
	     printk(KERN_INFO "%s CVBS output\n", stdstr);
	     ivideo->vbflags |= TV_AVIDEO;
	     SiS_SetRegOR(SISCR, 0x32, 0x01);
	     SiS_SetRegAND(SISCR, 0x32, ~0x06);
	     break;
	case 0x02:
	     printk(KERN_INFO "%s SVIDEO output\n", stdstr);
	     ivideo->vbflags |= TV_SVIDEO;
	     SiS_SetRegOR(SISCR, 0x32, 0x02);
	     SiS_SetRegAND(SISCR, 0x32, ~0x05);
	     break;
	case 0x04:
	     printk(KERN_INFO "%s SCART output\n", stdstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x04);
	     SiS_SetRegAND(SISCR, 0x32, ~0x03);
	     break;
	default:
	     SiS_SetRegAND(SISCR, 0x32, ~0x07);
	}
#endif
    }
}