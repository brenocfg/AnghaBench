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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int* PUCHAR ;

/* Variables and functions */
 unsigned int BytesPerPixel ; 
 unsigned int CHAR_HEIGHT ; 
 unsigned int CHAR_WIDTH ; 
 unsigned int Delta ; 
 scalar_t__ FrameBuffer ; 
 unsigned int TOP_BOTTOM_LINES ; 
 int* XboxFont8x16 ; 

__attribute__((used)) static VOID
XboxVideoOutputChar(UCHAR Char, unsigned X, unsigned Y, ULONG FgColor, ULONG BgColor)
{
  PUCHAR FontPtr;
  PULONG Pixel;
  UCHAR Mask;
  unsigned Line;
  unsigned Col;

  FontPtr = XboxFont8x16 + Char * 16;
  Pixel = (PULONG) ((char *) FrameBuffer + (Y * CHAR_HEIGHT + TOP_BOTTOM_LINES) * Delta
                  + X * CHAR_WIDTH * BytesPerPixel);
  for (Line = 0; Line < CHAR_HEIGHT; Line++)
    {
      Mask = 0x80;
      for (Col = 0; Col < CHAR_WIDTH; Col++)
        {
          Pixel[Col] = (0 != (FontPtr[Line] & Mask) ? FgColor : BgColor);
          Mask = Mask >> 1;
        }
      Pixel = (PULONG) ((char *) Pixel + Delta);
    }
}