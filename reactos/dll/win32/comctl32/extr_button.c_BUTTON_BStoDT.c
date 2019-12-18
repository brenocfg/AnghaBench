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
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
#define  BS_BOTTOM 133 
#define  BS_CENTER 132 
 scalar_t__ BS_DEFPUSHBUTTON ; 
 scalar_t__ BS_GROUPBOX ; 
#define  BS_LEFT 131 
 int BS_MULTILINE ; 
 int BS_PUSHLIKE ; 
#define  BS_RIGHT 130 
#define  BS_TOP 129 
 int BS_TYPEMASK ; 
#define  BS_VCENTER 128 
 int DT_BOTTOM ; 
 int DT_CENTER ; 
 int DT_LEFT ; 
 int DT_NOCLIP ; 
 int DT_RIGHT ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int DT_WORDBREAK ; 
 int WS_EX_RIGHT ; 
 scalar_t__ get_button_type (int) ; 

__attribute__((used)) static UINT BUTTON_BStoDT( DWORD style, DWORD ex_style )
{
    UINT dtStyle = DT_NOCLIP;  /* We use SelectClipRgn to limit output */

    /* "Convert" pushlike buttons to pushbuttons */
    if (style & BS_PUSHLIKE)
        style &= ~BS_TYPEMASK;

    if (!(style & BS_MULTILINE))
        dtStyle |= DT_SINGLELINE;
    else
        dtStyle |= DT_WORDBREAK;

    switch (style & BS_CENTER)
    {
        case BS_LEFT:   /* DT_LEFT is 0 */    break;
        case BS_RIGHT:  dtStyle |= DT_RIGHT;  break;
        case BS_CENTER: dtStyle |= DT_CENTER; break;
        default:
            /* Pushbutton's text is centered by default */
            if (get_button_type(style) <= BS_DEFPUSHBUTTON) dtStyle |= DT_CENTER;
            /* all other flavours have left aligned text */
    }

    if (ex_style & WS_EX_RIGHT) dtStyle = DT_RIGHT | (dtStyle & ~(DT_LEFT | DT_CENTER));

    /* DrawText ignores vertical alignment for multiline text,
     * but we use these flags to align label manually.
     */
    if (get_button_type(style) != BS_GROUPBOX)
    {
        switch (style & BS_VCENTER)
        {
            case BS_TOP:     /* DT_TOP is 0 */      break;
            case BS_BOTTOM:  dtStyle |= DT_BOTTOM;  break;
            case BS_VCENTER: /* fall through */
            default:         dtStyle |= DT_VCENTER; break;
        }
    }
    else
        /* GroupBox's text is always single line and is top aligned. */
        dtStyle |= DT_SINGLELINE;

    return dtStyle;
}