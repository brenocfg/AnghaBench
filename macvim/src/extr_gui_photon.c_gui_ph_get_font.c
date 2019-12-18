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
typedef  int int_u ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_3__ {scalar_t__ size; int style; } ;
typedef  int /*<<< orphan*/ * GuiFont ;
typedef  TYPE_1__ FontQueryInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FONT_TAG ; 
 int PF_STYLE_ANTIALIAS ; 
 int PF_STYLE_BOLD ; 
 int PF_STYLE_ITALIC ; 
 int PHFONT_INFO_ALIAS ; 
 int PHFONT_INFO_BOLD ; 
 int PHFONT_INFO_FIXED ; 
 int PHFONT_INFO_ITALIC ; 
 int /*<<< orphan*/ * PfGenerateFontName (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PfQueryFontInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GuiFont
gui_ph_get_font(
	char_u	*font_name,
	int_u	font_flags,
	int_u	font_size,
	/* Check whether the resulting font has the font flags and size that
	 * was asked for */
	int_u	enforce
	)
{
    char_u	    *font_tag;
    FontQueryInfo   info;
    int_u	    style;

    font_tag = alloc(MAX_FONT_TAG);
    if (font_tag != NULL)
    {
	if (PfGenerateFontName(font_name, font_flags, font_size,
		    font_tag) != NULL)
	{
	    /* Enforce some limits on the font used */
	    style = PHFONT_INFO_FIXED;

	    if (enforce & PF_STYLE_BOLD)
		style |= PHFONT_INFO_BOLD;
	    if (enforce & PF_STYLE_ANTIALIAS)
		style |= PHFONT_INFO_ALIAS;
	    if (enforce & PF_STYLE_ITALIC)
		style |= PHFONT_INFO_ITALIC;

	    PfQueryFontInfo(font_tag, &info);

	    if (info.size == 0)
		font_size = 0;

	    /* Make sure font size matches, and that the font style
	     * at least has the bits we're checking for */
	    if (font_size == info.size &&
		    style == (info.style & style))
		return (GuiFont)font_tag;
	}
	vim_free(font_tag);
    }
    return NULL;
}