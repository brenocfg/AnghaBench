#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ascent; scalar_t__ descent; } ;
typedef  TYPE_1__ XFontStruct ;
struct TYPE_4__ {scalar_t__ char_ascent; scalar_t__ char_height; scalar_t__ norm_font; } ;

/* Variables and functions */
 int OK ; 
 TYPE_2__ gui ; 
 int p_linespace ; 

int
gui_mch_adjust_charheight()
{
#ifdef FEAT_XFONTSET
    if (gui.fontset != NOFONTSET)
    {
	gui.char_height = fontset_height((XFontSet)gui.fontset) + p_linespace;
	gui.char_ascent = fontset_ascent((XFontSet)gui.fontset)
							    + p_linespace / 2;
    }
    else
#endif
    {
	XFontStruct *font = (XFontStruct *)gui.norm_font;

	gui.char_height = font->ascent + font->descent + p_linespace;
	gui.char_ascent = font->ascent + p_linespace / 2;
    }
    return OK;
}