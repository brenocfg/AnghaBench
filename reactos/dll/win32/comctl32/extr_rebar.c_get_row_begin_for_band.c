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
struct TYPE_2__ {int iRow; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  int INT ;

/* Variables and functions */
 TYPE_1__* REBAR_GetBand (int /*<<< orphan*/  const*,int) ; 
 int prev_visible (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int get_row_begin_for_band(const REBAR_INFO *infoPtr, INT iBand)
{
    int iLastBand = iBand;
    int iRow = REBAR_GetBand(infoPtr, iBand)->iRow;
    while ((iBand = prev_visible(infoPtr, iBand)) >= 0) {
        if (REBAR_GetBand(infoPtr, iBand)->iRow != iRow)
            break;
        else
            iLastBand = iBand;
    }
    return iLastBand;
}