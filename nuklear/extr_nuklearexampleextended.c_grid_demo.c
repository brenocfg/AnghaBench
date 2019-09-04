#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nk_context {int dummy; } ;
struct media {TYPE_3__* font_14; TYPE_2__* font_18; TYPE_1__* font_20; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  NK_EDIT_FIELD ; 
 int /*<<< orphan*/  NK_TEXT_LEFT ; 
 int /*<<< orphan*/  NK_TEXT_RIGHT ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_NO_SCROLLBAR ; 
 int NK_WINDOW_TITLE ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_checkbox_label (struct nk_context*,char*,int*) ; 
 scalar_t__ nk_combo_begin_label (struct nk_context*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_combo_end (struct nk_context*) ; 
 scalar_t__ nk_combo_item_label (struct nk_context*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_edit_string (struct nk_context*,int /*<<< orphan*/ ,char*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_filter_binary ; 
 int /*<<< orphan*/  nk_filter_float ; 
 int /*<<< orphan*/  nk_filter_hex ; 
 int /*<<< orphan*/  nk_label (struct nk_context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_style_set_font (struct nk_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_vec2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_widget_width (struct nk_context*) ; 

__attribute__((used)) static void
grid_demo(struct nk_context *ctx, struct media *media)
{
    static char text[3][64];
    static int text_len[3];
    static const char *items[] = {"Item 0","item 1","item 2"};
    static int selected_item = 0;
    static int check = 1;

    int i;
    nk_style_set_font(ctx, &media->font_20->handle);
    if (nk_begin(ctx, "Grid Demo", nk_rect(600, 350, 275, 250),
        NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
        NK_WINDOW_NO_SCROLLBAR))
    {
        nk_style_set_font(ctx, &media->font_18->handle);
        nk_layout_row_dynamic(ctx, 30, 2);
        nk_label(ctx, "Floating point:", NK_TEXT_RIGHT);
        nk_edit_string(ctx, NK_EDIT_FIELD, text[0], &text_len[0], 64, nk_filter_float);
        nk_label(ctx, "Hexadecimal:", NK_TEXT_RIGHT);
        nk_edit_string(ctx, NK_EDIT_FIELD, text[1], &text_len[1], 64, nk_filter_hex);
        nk_label(ctx, "Binary:", NK_TEXT_RIGHT);
        nk_edit_string(ctx, NK_EDIT_FIELD, text[2], &text_len[2], 64, nk_filter_binary);
        nk_label(ctx, "Checkbox:", NK_TEXT_RIGHT);
        nk_checkbox_label(ctx, "Check me", &check);
        nk_label(ctx, "Combobox:", NK_TEXT_RIGHT);
        if (nk_combo_begin_label(ctx, items[selected_item], nk_vec2(nk_widget_width(ctx), 200))) {
            nk_layout_row_dynamic(ctx, 25, 1);
            for (i = 0; i < 3; ++i)
                if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
                    selected_item = i;
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
    nk_style_set_font(ctx, &media->font_14->handle);
}