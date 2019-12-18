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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PORT_UCHAR (int /*<<< orphan*/ *) ; 
 scalar_t__ VIDEOPORT_PALETTE_DATA ; 
 scalar_t__ VIDEOPORT_PALETTE_READ ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID
PcVideoGetPaletteColor(UCHAR Color, UCHAR* Red, UCHAR* Green, UCHAR* Blue)
{
  WRITE_PORT_UCHAR((UCHAR*) VIDEOPORT_PALETTE_READ, Color);
  *Red = READ_PORT_UCHAR((UCHAR*) VIDEOPORT_PALETTE_DATA);
  *Green = READ_PORT_UCHAR((UCHAR*) VIDEOPORT_PALETTE_DATA);
  *Blue = READ_PORT_UCHAR((UCHAR*) VIDEOPORT_PALETTE_DATA);
}