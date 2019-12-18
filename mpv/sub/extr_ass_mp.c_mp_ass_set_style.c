#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ a; } ;
struct osd_style_opts {double font_size; double border_size; double shadow_offset; double spacing; double margin_x; double margin_y; int align_y; int /*<<< orphan*/  italic; int /*<<< orphan*/  bold; int /*<<< orphan*/  blur; int /*<<< orphan*/  justify; scalar_t__ align_x; TYPE_3__ shadow_color; TYPE_3__ back_color; TYPE_3__ border_color; TYPE_3__ color; scalar_t__ font; } ;
struct TYPE_4__ {double FontSize; int BorderStyle; double Outline; double Shadow; double Spacing; double MarginL; double MarginR; double MarginV; int ScaleX; int ScaleY; int /*<<< orphan*/  Italic; int /*<<< orphan*/  Bold; int /*<<< orphan*/  Blur; int /*<<< orphan*/  Justify; scalar_t__ Alignment; void* BackColour; void* OutlineColour; void* PrimaryColour; void* SecondaryColour; scalar_t__ FontName; } ;
typedef  TYPE_1__ ASS_Style ;

/* Variables and functions */
 void* MP_ASS_COLOR (TYPE_3__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 scalar_t__ strdup (scalar_t__) ; 

void mp_ass_set_style(ASS_Style *style, double res_y,
                      const struct osd_style_opts *opts)
{
    if (!style)
        return;

    if (opts->font) {
        if (!style->FontName || strcmp(style->FontName, opts->font) != 0) {
            free(style->FontName);
            style->FontName = strdup(opts->font);
        }
    }

    // libass_font_size = FontSize * (window_height / res_y)
    // scale translates parameters from PlayResY=720 to res_y
    double scale = res_y / 720.0;

    style->FontSize = opts->font_size * scale;
    style->PrimaryColour = MP_ASS_COLOR(opts->color);
    style->SecondaryColour = style->PrimaryColour;
    style->OutlineColour = MP_ASS_COLOR(opts->border_color);
    if (opts->back_color.a) {
        style->BackColour = MP_ASS_COLOR(opts->back_color);
        style->BorderStyle = 4; // opaque box
    } else {
        style->BackColour = MP_ASS_COLOR(opts->shadow_color);
        style->BorderStyle = 1; // outline
    }
    style->Outline = opts->border_size * scale;
    style->Shadow = opts->shadow_offset * scale;
    style->Spacing = opts->spacing * scale;
    style->MarginL = opts->margin_x * scale;
    style->MarginR = style->MarginL;
    style->MarginV = opts->margin_y * scale;
    style->ScaleX = 1.;
    style->ScaleY = 1.;
    style->Alignment = 1 + (opts->align_x + 1) + (opts->align_y + 2) % 3 * 4;
#ifdef ASS_JUSTIFY_LEFT
    style->Justify = opts->justify;
#endif
    style->Blur = opts->blur;
    style->Bold = opts->bold;
    style->Italic = opts->italic;
}