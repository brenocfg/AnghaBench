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
typedef  int UINT ;
struct TYPE_3__ {int uLinesToScroll; } ;
typedef  TYPE_1__* LPSCROLLSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_GETWHEELSCROLLLINES ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

void UpdateLinesToScroll(LPSCROLLSTATE state)
{
    UINT uLinesToScroll;

    if (!SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &uLinesToScroll, 0))
    {
        /* Default value on Windows */
        state->uLinesToScroll = 3;
    }
    else
    {
        state->uLinesToScroll = uLinesToScroll;
    }
}