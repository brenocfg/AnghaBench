#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Blue; int /*<<< orphan*/  Green; int /*<<< orphan*/  Red; } ;
typedef  TYPE_1__* PPALETTE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  MachVideoSetPaletteColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MachVideoSync () ; 

VOID VideoRestorePaletteState(PPALETTE_ENTRY Palette, ULONG ColorCount)
{
    ULONG Color;

    MachVideoSync();

    for (Color = 0; Color < ColorCount; Color++)
    {
        MachVideoSetPaletteColor((UCHAR)Color, Palette[Color].Red, Palette[Color].Green, Palette[Color].Blue);
    }
}