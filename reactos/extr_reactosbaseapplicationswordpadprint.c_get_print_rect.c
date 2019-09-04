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
struct TYPE_2__ {scalar_t__ bottom; scalar_t__ right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 int GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  PHYSICALHEIGHT ; 
 int /*<<< orphan*/  PHYSICALWIDTH ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int centmm_to_twips (int) ; 
 int devunits_to_twips (int,int) ; 
 TYPE_1__ margins ; 

__attribute__((used)) static RECT get_print_rect(HDC hdc)
{
    RECT rc;
    int width, height;

    if(hdc)
    {
        int dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
        int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
        width = devunits_to_twips(GetDeviceCaps(hdc, PHYSICALWIDTH), dpiX);
        height = devunits_to_twips(GetDeviceCaps(hdc, PHYSICALHEIGHT), dpiY);
    } else
    {
        width = centmm_to_twips(18500);
        height = centmm_to_twips(27000);
    }

    SetRect(&rc, margins.left, margins.top, width - margins.right, height - margins.bottom);

    return rc;
}