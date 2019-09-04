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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int CHAR_HEIGHT ; 
 int CHAR_WIDTH ; 
 int ScreenHeight ; 
 int ScreenWidth ; 
 int TOP_BOTTOM_LINES ; 
 int /*<<< orphan*/  XboxVideoPutChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

VOID
XboxVideoCopyOffScreenBufferToVRAM(PVOID Buffer)
{
  PUCHAR OffScreenBuffer = (PUCHAR) Buffer;
  ULONG Col, Line;

  for (Line = 0; Line < (ScreenHeight - 2 * TOP_BOTTOM_LINES) / CHAR_HEIGHT; Line++)
    {
      for (Col = 0; Col < ScreenWidth / CHAR_WIDTH; Col++)
        {
          XboxVideoPutChar(OffScreenBuffer[0], OffScreenBuffer[1], Col, Line);
          OffScreenBuffer += 2;
        }
    }
}