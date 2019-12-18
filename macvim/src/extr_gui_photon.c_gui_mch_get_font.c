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
typedef  int int_u ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  GuiFont ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  e_font ; 
 int /*<<< orphan*/ * gui_ph_get_font (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ gui_ph_parse_font_name (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

GuiFont
gui_mch_get_font(char_u *vim_font_name, int report_error)
{
    char_u  *font_name;
    char_u  *font_tag;
    int_u   font_size = 12;
    int_u   font_flags = 0;

    if (gui_ph_parse_font_name(vim_font_name, &font_name, &font_flags,
		&font_size) != FALSE)
    {
	font_tag = gui_ph_get_font(font_name, font_flags, font_size, -1);
	vim_free(font_name);

	if (font_tag != NULL)
	    return (GuiFont)font_tag;
    }

    if (report_error)
	EMSG2(e_font, vim_font_name);

    return FAIL;
}