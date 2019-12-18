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
struct TYPE_4__ {int dwEffects; int bUnderlineType; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ ME_Style ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int CFE_LINK ; 
 int CFE_UNDERLINE ; 
#define  CFU_CF1UNDERLINE 133 
#define  CFU_UNDERLINE 132 
#define  CFU_UNDERLINEDOTTED 131 
#define  CFU_UNDERLINEDOUBLE 130 
#define  CFU_UNDERLINENONE 129 
#define  CFU_UNDERLINEWORD 128 
 int /*<<< orphan*/ * CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  PS_DOT ; 
 int /*<<< orphan*/  PS_SOLID ; 

__attribute__((used)) static HPEN get_underline_pen( ME_Style *style, COLORREF color )
{
    if (style->fmt.dwEffects & CFE_LINK)
        return CreatePen( PS_SOLID, 1, color );

    /* Choose the pen type for underlining the text. */
    if (style->fmt.dwEffects & CFE_UNDERLINE)
    {
        switch (style->fmt.bUnderlineType)
        {
        case CFU_UNDERLINE:
        case CFU_UNDERLINEWORD: /* native seems to map it to simple underline (MSDN) */
        case CFU_UNDERLINEDOUBLE: /* native seems to map it to simple underline (MSDN) */
            return CreatePen( PS_SOLID, 1, color );
        case CFU_UNDERLINEDOTTED:
            return CreatePen( PS_DOT, 1, color );
        default:
            FIXME( "Unknown underline type (%u)\n", style->fmt.bUnderlineType );
            /* fall through */
        case CFU_CF1UNDERLINE: /* this type is supported in the font, do nothing */
        case CFU_UNDERLINENONE:
            break;
        }
    }
    return NULL;
}