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
struct TYPE_5__ {int char_ascent; scalar_t__ char_height; int /*<<< orphan*/  norm_font; } ;
struct TYPE_4__ {int ascender; scalar_t__ descender; } ;
typedef  TYPE_1__ FontQueryInfo ;

/* Variables and functions */
 int OK ; 
 int /*<<< orphan*/  PfQueryFontInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ gui ; 
 int p_linespace ; 

int
gui_mch_adjust_charheight(void)
{
    FontQueryInfo info;

    PfQueryFontInfo(gui.norm_font, &info);

    gui.char_height = - info.ascender + info.descender + p_linespace;
    gui.char_ascent = - info.ascender + p_linespace / 2;

    return OK;
}