#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct node_link {scalar_t__ output_slot; scalar_t__ input_slot; int /*<<< orphan*/  output_id; int /*<<< orphan*/  input_id; } ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int input_slot; struct node* node; void* active; int /*<<< orphan*/  input_id; } ;
struct node_editor {int initialized; int show_grid; int link_count; TYPE_2__ scrolling; struct node* selected; int /*<<< orphan*/  bounds; struct node* begin; struct node_link* links; TYPE_1__ linking; struct node* end; int /*<<< orphan*/  node_count; } ;
struct nk_rect {float h; int x; float w; int y; } ;
struct TYPE_10__ {void* a; void* b; void* g; void* r; } ;
struct node {int output_count; int input_count; struct node* next; struct nk_rect bounds; int /*<<< orphan*/  ID; TYPE_5__ color; scalar_t__ prev; int /*<<< orphan*/  name; } ;
struct nk_vec2 {int x; int y; } ;
struct nk_panel {struct nk_rect bounds; } ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_9__ {TYPE_3__ delta; struct nk_vec2 pos; } ;
struct nk_input {TYPE_4__ mouse; } ;
struct nk_context {struct nk_input input; } ;
struct nk_command_buffer {int dummy; } ;
struct nk_color {int dummy; } ;
typedef  void* nk_byte ;

/* Variables and functions */
 int /*<<< orphan*/  NK_BUTTON_LEFT ; 
 int /*<<< orphan*/  NK_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  NK_STATIC ; 
 int /*<<< orphan*/  NK_TEXT_CENTERED ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_CLOSABLE ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_NO_SCROLLBAR ; 
 int NK_WINDOW_TITLE ; 
 scalar_t__ fmod (int,float const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_button_color (struct nk_context*,TYPE_5__) ; 
 scalar_t__ nk_contextual_begin (struct nk_context*,int /*<<< orphan*/ ,struct nk_vec2,struct nk_rect) ; 
 int /*<<< orphan*/  nk_contextual_end (struct nk_context*) ; 
 scalar_t__ nk_contextual_item_label (struct nk_context*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 void* nk_false ; 
 int /*<<< orphan*/  nk_fill_circle (struct nk_command_buffer*,struct nk_rect,struct nk_color) ; 
 scalar_t__ nk_group_begin (struct nk_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_group_end (struct nk_context*) ; 
 scalar_t__ nk_input_has_mouse_click_down_in_rect (struct nk_input const*,int /*<<< orphan*/ ,struct nk_rect,void*) ; 
 scalar_t__ nk_input_is_mouse_down (struct nk_input const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nk_input_is_mouse_hovering_rect (struct nk_input const*,struct nk_rect) ; 
 scalar_t__ nk_input_is_mouse_released (struct nk_input const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nk_input_mouse_clicked (struct nk_input const*,int /*<<< orphan*/ ,struct nk_rect) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_layout_space_begin (struct nk_context*,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 struct nk_rect nk_layout_space_bounds (struct nk_context*) ; 
 int /*<<< orphan*/  nk_layout_space_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_layout_space_push (struct nk_context*,int /*<<< orphan*/ ) ; 
 struct nk_rect nk_layout_space_rect_to_local (struct nk_context*,struct nk_rect) ; 
 struct nk_rect nk_layout_space_rect_to_screen (struct nk_context*,struct nk_rect) ; 
 struct nk_vec2 nk_layout_space_to_screen (struct nk_context*,struct nk_vec2) ; 
 scalar_t__ nk_propertyi (struct nk_context*,char*,int /*<<< orphan*/ ,void*,int,int,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 struct nk_color nk_rgb (int,int,int) ; 
 int /*<<< orphan*/  nk_stroke_curve (struct nk_command_buffer*,int,int,int,int,int,int,int,int,float,struct nk_color) ; 
 int /*<<< orphan*/  nk_stroke_line (struct nk_command_buffer*,int,int,int,int,float,struct nk_color const) ; 
 void* nk_true ; 
 struct nk_vec2 nk_vec2 (int,int) ; 
 struct nk_rect nk_window_get_bounds (struct nk_context*) ; 
 struct nk_command_buffer* nk_window_get_canvas (struct nk_context*) ; 
 struct nk_rect nk_window_get_content_region (struct nk_context*) ; 
 struct nk_panel* nk_window_get_panel (struct nk_context*) ; 
 int /*<<< orphan*/  nk_window_is_closed (struct nk_context*,char*) ; 
 struct node_editor nodeEditor ; 
 int /*<<< orphan*/  node_editor_add (struct node_editor*,char*,int /*<<< orphan*/ ,struct nk_color,int,int) ; 
 struct node* node_editor_find (struct node_editor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_editor_init (struct node_editor*) ; 
 int /*<<< orphan*/  node_editor_link (struct node_editor*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  node_editor_pop (struct node_editor*,struct node*) ; 
 int /*<<< orphan*/  node_editor_push (struct node_editor*,struct node*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
node_editor(struct nk_context *ctx)
{
    int n = 0;
    struct nk_rect total_space;
    const struct nk_input *in = &ctx->input;
    struct nk_command_buffer *canvas;
    struct node *updated = 0;
    struct node_editor *nodedit = &nodeEditor;

    if (!nodeEditor.initialized) {
        node_editor_init(&nodeEditor);
        nodeEditor.initialized = 1;
    }

    if (nk_begin(ctx, "NodeEdit", nk_rect(0, 0, 800, 600),
        NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE))
    {
        /* allocate complete window space */
        canvas = nk_window_get_canvas(ctx);
        total_space = nk_window_get_content_region(ctx);
        nk_layout_space_begin(ctx, NK_STATIC, total_space.h, nodedit->node_count);
        {
            struct node *it = nodedit->begin;
            struct nk_rect size = nk_layout_space_bounds(ctx);
            struct nk_panel *node = 0;

            if (nodedit->show_grid) {
                /* display grid */
                float x, y;
                const float grid_size = 32.0f;
                const struct nk_color grid_color = nk_rgb(50, 50, 50);
                for (x = (float)fmod(size.x - nodedit->scrolling.x, grid_size); x < size.w; x += grid_size)
                    nk_stroke_line(canvas, x+size.x, size.y, x+size.x, size.y+size.h, 1.0f, grid_color);
                for (y = (float)fmod(size.y - nodedit->scrolling.y, grid_size); y < size.h; y += grid_size)
                    nk_stroke_line(canvas, size.x, y+size.y, size.x+size.w, y+size.y, 1.0f, grid_color);
            }

            /* execute each node as a movable group */
            while (it) {
                /* calculate scrolled node window position and size */
                nk_layout_space_push(ctx, nk_rect(it->bounds.x - nodedit->scrolling.x,
                    it->bounds.y - nodedit->scrolling.y, it->bounds.w, it->bounds.h));

                /* execute node window */
                if (nk_group_begin(ctx, it->name, NK_WINDOW_MOVABLE|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_BORDER|NK_WINDOW_TITLE))
                {
                    /* always have last selected node on top */

                    node = nk_window_get_panel(ctx);
                    if (nk_input_mouse_clicked(in, NK_BUTTON_LEFT, node->bounds) &&
                        (!(it->prev && nk_input_mouse_clicked(in, NK_BUTTON_LEFT,
                        nk_layout_space_rect_to_screen(ctx, node->bounds)))) &&
                        nodedit->end != it)
                    {
                        updated = it;
                    }

                    /* ================= NODE CONTENT =====================*/
                    nk_layout_row_dynamic(ctx, 25, 1);
                    nk_button_color(ctx, it->color);
                    it->color.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, it->color.r, 255, 1,1);
                    it->color.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, it->color.g, 255, 1,1);
                    it->color.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, it->color.b, 255, 1,1);
                    it->color.a = (nk_byte)nk_propertyi(ctx, "#A:", 0, it->color.a, 255, 1,1);
                    /* ====================================================*/
                    nk_group_end(ctx);
                }
                {
                    /* node connector and linking */
                    float space;
                    struct nk_rect bounds;
                    bounds = nk_layout_space_rect_to_local(ctx, node->bounds);
                    bounds.x += nodedit->scrolling.x;
                    bounds.y += nodedit->scrolling.y;
                    it->bounds = bounds;

                    /* output connector */
                    space = node->bounds.h / (float)((it->output_count) + 1);
                    for (n = 0; n < it->output_count; ++n) {
                        struct nk_rect circle;
                        circle.x = node->bounds.x + node->bounds.w-4;
                        circle.y = node->bounds.y + space * (float)(n+1);
                        circle.w = 8; circle.h = 8;
                        nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));

                        /* start linking process */
                        if (nk_input_has_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, circle, nk_true)) {
                            nodedit->linking.active = nk_true;
                            nodedit->linking.node = it;
                            nodedit->linking.input_id = it->ID;
                            nodedit->linking.input_slot = n;
                        }

                        /* draw curve from linked node slot to mouse position */
                        if (nodedit->linking.active && nodedit->linking.node == it &&
                            nodedit->linking.input_slot == n) {
                            struct nk_vec2 l0 = nk_vec2(circle.x + 3, circle.y + 3);
                            struct nk_vec2 l1 = in->mouse.pos;
                            nk_stroke_curve(canvas, l0.x, l0.y, l0.x + 50.0f, l0.y,
                                l1.x - 50.0f, l1.y, l1.x, l1.y, 1.0f, nk_rgb(100, 100, 100));
                        }
                    }

                    /* input connector */
                    space = node->bounds.h / (float)((it->input_count) + 1);
                    for (n = 0; n < it->input_count; ++n) {
                        struct nk_rect circle;
                        circle.x = node->bounds.x-4;
                        circle.y = node->bounds.y + space * (float)(n+1);
                        circle.w = 8; circle.h = 8;
                        nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));
                        if (nk_input_is_mouse_released(in, NK_BUTTON_LEFT) &&
                            nk_input_is_mouse_hovering_rect(in, circle) &&
                            nodedit->linking.active && nodedit->linking.node != it) {
                            nodedit->linking.active = nk_false;
                            node_editor_link(nodedit, nodedit->linking.input_id,
                                nodedit->linking.input_slot, it->ID, n);
                        }
                    }
                }
                it = it->next;
            }

            /* reset linking connection */
            if (nodedit->linking.active && nk_input_is_mouse_released(in, NK_BUTTON_LEFT)) {
                nodedit->linking.active = nk_false;
                nodedit->linking.node = NULL;
                fprintf(stdout, "linking failed\n");
            }

            /* draw each link */
            for (n = 0; n < nodedit->link_count; ++n) {
                struct node_link *link = &nodedit->links[n];
                struct node *ni = node_editor_find(nodedit, link->input_id);
                struct node *no = node_editor_find(nodedit, link->output_id);
                float spacei = node->bounds.h / (float)((ni->output_count) + 1);
                float spaceo = node->bounds.h / (float)((no->input_count) + 1);
                struct nk_vec2 l0 = nk_layout_space_to_screen(ctx,
                    nk_vec2(ni->bounds.x + ni->bounds.w, 3.0f + ni->bounds.y + spacei * (float)(link->input_slot+1)));
                struct nk_vec2 l1 = nk_layout_space_to_screen(ctx,
                    nk_vec2(no->bounds.x, 3.0f + no->bounds.y + spaceo * (float)(link->output_slot+1)));

                l0.x -= nodedit->scrolling.x;
                l0.y -= nodedit->scrolling.y;
                l1.x -= nodedit->scrolling.x;
                l1.y -= nodedit->scrolling.y;
                nk_stroke_curve(canvas, l0.x, l0.y, l0.x + 50.0f, l0.y,
                    l1.x - 50.0f, l1.y, l1.x, l1.y, 1.0f, nk_rgb(100, 100, 100));
            }

            if (updated) {
                /* reshuffle nodes to have least recently selected node on top */
                node_editor_pop(nodedit, updated);
                node_editor_push(nodedit, updated);
            }

            /* node selection */
            if (nk_input_mouse_clicked(in, NK_BUTTON_LEFT, nk_layout_space_bounds(ctx))) {
                it = nodedit->begin;
                nodedit->selected = NULL;
                nodedit->bounds = nk_rect(in->mouse.pos.x, in->mouse.pos.y, 100, 200);
                while (it) {
                    struct nk_rect b = nk_layout_space_rect_to_screen(ctx, it->bounds);
                    b.x -= nodedit->scrolling.x;
                    b.y -= nodedit->scrolling.y;
                    if (nk_input_is_mouse_hovering_rect(in, b))
                        nodedit->selected = it;
                    it = it->next;
                }
            }

            /* contextual menu */
            if (nk_contextual_begin(ctx, 0, nk_vec2(100, 220), nk_window_get_bounds(ctx))) {
                const char *grid_option[] = {"Show Grid", "Hide Grid"};
                nk_layout_row_dynamic(ctx, 25, 1);
                if (nk_contextual_item_label(ctx, "New", NK_TEXT_CENTERED))
                    node_editor_add(nodedit, "New", nk_rect(400, 260, 180, 220),
                            nk_rgb(255, 255, 255), 1, 2);
                if (nk_contextual_item_label(ctx, grid_option[nodedit->show_grid],NK_TEXT_CENTERED))
                    nodedit->show_grid = !nodedit->show_grid;
                nk_contextual_end(ctx);
            }
        }
        nk_layout_space_end(ctx);

        /* window content scrolling */
        if (nk_input_is_mouse_hovering_rect(in, nk_window_get_bounds(ctx)) &&
            nk_input_is_mouse_down(in, NK_BUTTON_MIDDLE)) {
            nodedit->scrolling.x += in->mouse.delta.x;
            nodedit->scrolling.y += in->mouse.delta.y;
        }
    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "NodeEdit");
}