#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int BitsPerPixel; int GreenMaskSize; } ;
typedef  int* PULONG ;

/* Variables and functions */
 scalar_t__ DisplayMode ; 
 int ScreenHeight ; 
 int ScreenWidth ; 
 scalar_t__ VesaVideoMode ; 
 TYPE_1__ VesaVideoModeInformation ; 
 scalar_t__ VideoGraphicsMode ; 

VOID
PcVideoGetDisplaySize(PULONG Width, PULONG Height, PULONG Depth)
{
  *Width = ScreenWidth;
  *Height = ScreenHeight;
  if (VideoGraphicsMode == DisplayMode && VesaVideoMode)
    {
      if (16 == VesaVideoModeInformation.BitsPerPixel)
        {
          /* 16-bit color modes give green an extra bit (5:6:5)
           * 15-bit color modes have just 5:5:5 for R:G:B */
          *Depth = (6 == VesaVideoModeInformation.GreenMaskSize ? 16 : 15);
        }
      else
        {
          *Depth = VesaVideoModeInformation.BitsPerPixel;
        }
    }
  else
    {
      *Depth = 0;
    }
}