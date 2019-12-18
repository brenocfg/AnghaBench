#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nk_context {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  NkAllegro5Font ;
typedef  int /*<<< orphan*/  ALLEGRO_TIMEOUT ;
typedef  int /*<<< orphan*/  ALLEGRO_EVENT_QUEUE ;
typedef  TYPE_1__ ALLEGRO_EVENT ;
typedef  int /*<<< orphan*/  ALLEGRO_DISPLAY ;

/* Variables and functions */
 scalar_t__ ALLEGRO_EVENT_DISPLAY_CLOSE ; 
 int ALLEGRO_OPENGL ; 
 int ALLEGRO_RESIZABLE ; 
 int /*<<< orphan*/  ALLEGRO_SAMPLES ; 
 int /*<<< orphan*/  ALLEGRO_SAMPLE_BUFFERS ; 
 int /*<<< orphan*/  ALLEGRO_SUGGEST ; 
 int ALLEGRO_WINDOWED ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_CLOSABLE ; 
 int NK_WINDOW_MINIMIZABLE ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_SCALABLE ; 
 int NK_WINDOW_TITLE ; 
 int /*<<< orphan*/  WINDOW_HEIGHT ; 
 int /*<<< orphan*/  WINDOW_WIDTH ; 
 int /*<<< orphan*/  al_clear_to_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * al_create_display (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * al_create_event_queue () ; 
 int /*<<< orphan*/  al_destroy_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_destroy_event_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_flip_display () ; 
 int /*<<< orphan*/  al_get_display_event_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_get_keyboard_event_source () ; 
 int /*<<< orphan*/  al_get_mouse_event_source () ; 
 int al_get_next_event (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  al_init () ; 
 int /*<<< orphan*/  al_init_timeout (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  al_install_keyboard () ; 
 int /*<<< orphan*/  al_install_mouse () ; 
 int /*<<< orphan*/  al_map_rgb (int,int,int) ; 
 int /*<<< orphan*/  al_register_event_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_set_mouse_wheel_precision (int) ; 
 int /*<<< orphan*/  al_set_new_display_flags (int) ; 
 int /*<<< orphan*/  al_set_new_display_option (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int al_wait_for_event_until (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * nk_allegro5_font_create_from_file (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_allegro5_font_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_allegro5_handle_event (TYPE_1__*) ; 
 struct nk_context* nk_allegro5_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_allegro5_render () ; 
 int /*<<< orphan*/  nk_allegro5_shutdown () ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_button_label (struct nk_context*,char*) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_layout_row_static (struct nk_context*,int,int,int) ; 
 scalar_t__ nk_option_label (struct nk_context*,char*,int) ; 
 int /*<<< orphan*/  nk_property_int (struct nk_context*,char*,int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  overview (struct nk_context*) ; 
 int /*<<< orphan*/  stdout ; 

int main(void)
{
    /* Platform */
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if (!al_init()) {
        fprintf(stdout, "failed to initialize allegro5!\n");
        exit(1);
    }

    al_install_mouse();
    al_set_mouse_wheel_precision(150);
    al_install_keyboard();

    al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE|ALLEGRO_OPENGL);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!display) {
        fprintf(stdout, "failed to create display!\n");
        exit(1);
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stdout, "failed to create event_queue!\n");
        al_destroy_display(display);
        exit(1);
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    NkAllegro5Font *font;
    font = nk_allegro5_font_create_from_file("../../../extra_font/Roboto-Regular.ttf", 12, 0);
    struct nk_context *ctx;

    ctx = nk_allegro5_init(font, display, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* style.c */
    /*set_style(ctx, THEME_WHITE);*/
    /*set_style(ctx, THEME_RED);*/
    /*set_style(ctx, THEME_BLUE);*/
    /*set_style(ctx, THEME_DARK);*/

    while(1)
    {
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);

        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

        if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        /* Very Important: Always do nk_input_begin / nk_input_end even if
           there are no events, otherwise internal nuklear state gets messed up */
        nk_input_begin(ctx);
        if (get_event) {
            while (get_event) {
                nk_allegro5_handle_event(&ev);
                get_event = al_get_next_event(event_queue, &ev);
            }
        }
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 200, 200),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 22, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(ctx);

        /* -------------- EXAMPLES ---------------- */
        /*calculator(ctx);*/
        overview(ctx);
        /*node_editor(ctx);*/
        /* ----------------------------------------- */

        /* Draw */
        al_clear_to_color(al_map_rgb(19, 43, 81));
        /* IMPORTANT: `nk_allegro5_render` changes the target backbuffer
        to the display set at initialization and does not restore it.
        Change it if you want to draw somewhere else. */
        nk_allegro5_render();
        al_flip_display();
    }

    nk_allegro5_font_del(font);
    nk_allegro5_shutdown();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}