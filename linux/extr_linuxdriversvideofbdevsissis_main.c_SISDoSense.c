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
typedef  int u16 ;
struct sis_video_info {int /*<<< orphan*/  SiS_Pr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISPART4 ; 
 int /*<<< orphan*/  SiS_DDC2Delay (int /*<<< orphan*/ *,int) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int SISDoSense(struct sis_video_info *ivideo, u16 type, u16 test)
{
    int temp, mytest, result, i, j;

    for(j = 0; j < 10; j++) {
       result = 0;
       for(i = 0; i < 3; i++) {
          mytest = test;
	   SiS_SetReg(SISPART4, 0x11, (type & 0x00ff));
          temp = (type >> 8) | (mytest & 0x00ff);
	  SiS_SetRegANDOR(SISPART4, 0x10, 0xe0, temp);
          SiS_DDC2Delay(&ivideo->SiS_Pr, 0x1500);
          mytest >>= 8;
          mytest &= 0x7f;
	   temp = SiS_GetReg(SISPART4, 0x03);
          temp ^= 0x0e;
          temp &= mytest;
          if(temp == mytest) result++;
#if 1
	  SiS_SetReg(SISPART4, 0x11, 0x00);
	  SiS_SetRegAND(SISPART4, 0x10, 0xe0);
	  SiS_DDC2Delay(&ivideo->SiS_Pr, 0x1000);
#endif
       }
       if((result == 0) || (result >= 2)) break;
    }
    return result;
}