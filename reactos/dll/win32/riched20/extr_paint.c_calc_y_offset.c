#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwMask; int dwEffects; int yOffset; int yHeight; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ ME_Style ;
typedef  int /*<<< orphan*/  ME_Context ;

/* Variables and functions */
 int CFE_SUBSCRIPT ; 
 int CFE_SUPERSCRIPT ; 
 int CFM_OFFSET ; 
 int CFM_SUBSCRIPT ; 
 int CFM_SUPERSCRIPT ; 
 int ME_twips2pointsY (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int calc_y_offset( const ME_Context *c, ME_Style *style )
{
    int offs = 0, twips = 0;

    if ((style->fmt.dwMask & style->fmt.dwEffects) & CFM_OFFSET)
        twips = style->fmt.yOffset;

    if ((style->fmt.dwMask & style->fmt.dwEffects) & (CFM_SUPERSCRIPT | CFM_SUBSCRIPT))
    {
        if (style->fmt.dwEffects & CFE_SUPERSCRIPT) twips = style->fmt.yHeight/3;
        if (style->fmt.dwEffects & CFE_SUBSCRIPT) twips = -style->fmt.yHeight/12;
    }

    if (twips) offs = ME_twips2pointsY( c, twips );

    return offs;
}