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
struct TYPE_2__ {int font_can_bold; int /*<<< orphan*/  text_context; int /*<<< orphan*/ * norm_font; } ;
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoFont ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PANGO_WEIGHT_BOLD ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/ * pango_context_load_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_font_description_copy_static (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_set_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_styled_font_variants(void)
{
    PangoFontDescription    *bold_font_desc;
    PangoFont		    *plain_font;
    PangoFont		    *bold_font;

    gui.font_can_bold = FALSE;

    plain_font = pango_context_load_font(gui.text_context, gui.norm_font);

    if (plain_font == NULL)
	return;

    bold_font_desc = pango_font_description_copy_static(gui.norm_font);
    pango_font_description_set_weight(bold_font_desc, PANGO_WEIGHT_BOLD);

    bold_font = pango_context_load_font(gui.text_context, bold_font_desc);
    /*
     * The comparison relies on the unique handle nature of a PangoFont*,
     * i.e. it's assumed that a different PangoFont* won't refer to the
     * same font.  Seems to work, and failing here isn't critical anyway.
     */
    if (bold_font != NULL)
    {
	gui.font_can_bold = (bold_font != plain_font);
	g_object_unref(bold_font);
    }

    pango_font_description_free(bold_font_desc);
    g_object_unref(plain_font);
}