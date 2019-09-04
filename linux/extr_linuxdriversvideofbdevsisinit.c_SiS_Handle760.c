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
struct SiS_Private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
SiS_Handle760(struct SiS_Private *SiS_Pr)
{
#ifdef CONFIG_FB_SIS_315
   unsigned int somebase;
   unsigned char temp1, temp2, temp3;

   if( (SiS_Pr->ChipType != SIS_760)                         ||
       ((SiS_GetReg(SiS_Pr->SiS_P3d4, 0x5c) & 0xf8) != 0x80) ||
       (!(SiS_Pr->SiS_SysFlags & SF_760LFB))                 ||
       (!(SiS_Pr->SiS_SysFlags & SF_760UMA)) )
      return;

   somebase = sisfb_read_mio_pci_word(SiS_Pr, 0x74);
   somebase &= 0xffff;

   if(somebase == 0) return;

   temp3 = SiS_GetRegByte((somebase + 0x85)) & 0xb7;

   if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) {
      temp1 = 0x21;
      temp2 = 0x03;
      temp3 |= 0x08;
   } else {
      temp1 = 0x25;
      temp2 = 0x0b;
   }

   sisfb_write_nbridge_pci_byte(SiS_Pr, 0x7e, temp1);
   sisfb_write_nbridge_pci_byte(SiS_Pr, 0x8d, temp2);

   SiS_SetRegByte((somebase + 0x85), temp3);
#endif
}