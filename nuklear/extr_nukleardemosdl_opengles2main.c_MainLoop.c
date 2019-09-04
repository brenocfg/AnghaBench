#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nk_context {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  MAX_ELEMENT_MEMORY ; 
 int /*<<< orphan*/  MAX_VERTEX_MEMORY ; 
 int /*<<< orphan*/  NK_ANTI_ALIASING_ON ; 
 int /*<<< orphan*/  NK_STATIC ; 
 int /*<<< orphan*/  NK_TEXT_LEFT ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_CLOSABLE ; 
 int NK_WINDOW_MINIMIZABLE ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_SCALABLE ; 
 int NK_WINDOW_TITLE ; 
 int /*<<< orphan*/  SDL_GL_SwapWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ SDL_PollEvent (TYPE_1__*) ; 
 scalar_t__ SDL_QUIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_button_label (struct nk_context*,char*) ; 
 int /*<<< orphan*/  nk_color_fv (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_false ; 
 int /*<<< orphan*/  nk_input_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_layout_row_begin (struct nk_context*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_layout_row_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_layout_row_push (struct nk_context*,int) ; 
 int /*<<< orphan*/  nk_layout_row_static (struct nk_context*,int,int,int) ; 
 scalar_t__ nk_menu_begin_label (struct nk_context*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_menu_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_menu_item_label (struct nk_context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_menubar_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_menubar_end (struct nk_context*) ; 
 scalar_t__ nk_option_label (struct nk_context*,char*,int) ; 
 int /*<<< orphan*/  nk_property_int (struct nk_context*,char*,int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 int /*<<< orphan*/  nk_sdl_handle_event (TYPE_1__*) ; 
 int /*<<< orphan*/  nk_sdl_render (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_vec2 (int,int) ; 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  win ; 

__attribute__((used)) static void
MainLoop(void* loopArg){
    struct nk_context *ctx = (struct nk_context *)loopArg;

    /* Input */
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) running = nk_false;
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(ctx);


    /* GUI */
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 200, 200),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nk_menubar_begin(ctx);
        nk_layout_row_begin(ctx, NK_STATIC, 25, 2);
        nk_layout_row_push(ctx, 45);
        if (nk_menu_begin_label(ctx, "FILE", NK_TEXT_LEFT, nk_vec2(120, 200))) {
            nk_layout_row_dynamic(ctx, 30, 1);
            nk_menu_item_label(ctx, "OPEN", NK_TEXT_LEFT);
            nk_menu_item_label(ctx, "CLOSE", NK_TEXT_LEFT);
            nk_menu_end(ctx);
        }
        nk_layout_row_push(ctx, 45);
        if (nk_menu_begin_label(ctx, "EDIT", NK_TEXT_LEFT, nk_vec2(120, 200))) {
            nk_layout_row_dynamic(ctx, 30, 1);
            nk_menu_item_label(ctx, "COPY", NK_TEXT_LEFT);
            nk_menu_item_label(ctx, "CUT", NK_TEXT_LEFT);
            nk_menu_item_label(ctx, "PASTE", NK_TEXT_LEFT);
            nk_menu_end(ctx);
        }
        nk_layout_row_end(ctx);
        nk_menubar_end(ctx);

        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            fprintf(stdout, "button pressed\n");
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
    }
    nk_end(ctx);

    /* -------------- EXAMPLES ---------------- */
    /*calculator(ctx);*/
    /*overview(ctx);*/
    /*node_editor(ctx);*/
    /* ----------------------------------------- */

    /* Draw */
    {float bg[4];
    int win_width, win_height;
    nk_color_fv(bg, nk_rgb(28,48,62));
    SDL_GetWindowSize(win, &win_width, &win_height);
    glViewport(0, 0, win_width, win_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
    /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI. */
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(win);}
}