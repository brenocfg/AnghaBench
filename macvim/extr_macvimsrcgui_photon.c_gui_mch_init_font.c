#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int_u ;
typedef  char char_u ;
struct TYPE_12__ {char* norm_font; char* bold_font; char* ital_font; int /*<<< orphan*/  char_ascent; scalar_t__ char_height; scalar_t__ char_width; int /*<<< orphan*/  vimWindow; } ;
struct TYPE_11__ {int /*<<< orphan*/  font; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; scalar_t__ x; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_10__ {TYPE_2__ ul; TYPE_1__ lr; } ;
typedef  TYPE_3__ PhRect_t ;
typedef  TYPE_4__ FontQueryInfo ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ FALSE ; 
 int OK ; 
 int PF_STYLE_BOLD ; 
 int PF_STYLE_ITALIC ; 
 int /*<<< orphan*/  PHFONT_FIXED ; 
 int /*<<< orphan*/  PfExtentText (TYPE_3__*,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  PfQueryFontInfo (char*,TYPE_4__*) ; 
 char* PtFontSelection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STRCMP (char*,char*) ; 
 TYPE_5__ gui ; 
 int /*<<< orphan*/  gui_mch_free_font (char*) ; 
 void* gui_ph_get_font (char*,int,int,int) ; 
 scalar_t__ gui_ph_parse_font_name (char*,char**,int*,int*) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 char* vim_strsave (int /*<<< orphan*/ ) ; 

int
gui_mch_init_font(char_u *vim_font_name, int fontset)
{
    char_u  *font_tag;
    char_u  *font_name = NULL;
    int_u   font_flags = 0;
    int_u   font_size  = 12;

    FontQueryInfo info;
    PhRect_t extent;

    if (vim_font_name == NULL)
    {
	/* Default font */
	vim_font_name = "PC Terminal";
    }

    if (STRCMP(vim_font_name, "*") == 0)
    {
	font_tag = PtFontSelection(gui.vimWindow, NULL, NULL,
		"pcterm12", -1, PHFONT_FIXED, NULL);

	if (font_tag == NULL)
	    return FAIL;

	gui_mch_free_font(gui.norm_font);
	gui.norm_font = font_tag;

	PfQueryFontInfo(font_tag, &info);
	font_name = vim_strsave(info.font);
    }
    else
    {
	if (gui_ph_parse_font_name(vim_font_name, &font_name, &font_flags,
		    &font_size) == FALSE)
	    return FAIL;

	font_tag = gui_ph_get_font(font_name, font_flags, font_size, 0);
	if (font_tag == NULL)
	{
	    vim_free(font_name);
	    return FAIL;
	}

	gui_mch_free_font(gui.norm_font);
	gui.norm_font = font_tag;
    }

    gui_mch_free_font(gui.bold_font);
    gui.bold_font = gui_ph_get_font(font_name, font_flags | PF_STYLE_BOLD,
	    font_size, PF_STYLE_BOLD);

    gui_mch_free_font(gui.ital_font);
    gui.ital_font = gui_ph_get_font(font_name, font_flags | PF_STYLE_ITALIC,
	    font_size, PF_STYLE_ITALIC);

    /* This extent was brought to you by the letter 'g' */
    PfExtentText(&extent, NULL, font_tag, "g", 1);

    gui.char_width = extent.lr.x - extent.ul.x + 1;
    gui.char_height = (- extent.ul.y) + extent.lr.y + 1;
    gui.char_ascent = - extent.ul.y;

    vim_free(font_name);
    return OK;
}